/**
 * @file Window.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Window.h"

#include <mutex>
#include "src/Exception.hpp"
#include "InputInterface.h"

using namespace engine;


Window::Window() {
}

void Window::open() {

	onOpening();

	if (glfwInit() != GL_TRUE)
		throw zprException("Window::open", "GLFW initialization failed");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef DARWIN
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	glfw_window = glfwCreateWindow(window_width, window_height, getTitle().c_str(), nullptr, nullptr);

	if (glfw_window == nullptr)
		throw zprException("Window::open", "Can't open GLFW window_wptr");

	glfwMakeContextCurrent(glfw_window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw zprException("Window::open", "GLEW initialization failed");

	glEnable(GL_DEPTH_TEST);

//	vsync
//	glfwSwapInterval(0);

	// rysuj same linie, przydane do debugowania
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	initObjects();

	onOpened();

//	double lastTime = -1, nowTime = 0;
	while (!glfwWindowShouldClose(glfw_window)) {

//		lastTime = nowTime;
//		nowTime = glfwGetTime();
//		auto delta = nowTime - lastTime;
//		logger(1).log("fps").log(1 / delta);

		mainLoop();
		swapScene();
	}

	glfwTerminate();

	onClosed();
}

void Window::setScene(ScenePtr scene) {
	next_scene_ptr = scene;
	//TODO dodać zwracanie wyjątku kiedy jest już jakaś scena w kolejce
}

void Window::swapScene() {
	if (next_scene_ptr == nullptr) return;

	auto old_scene_ptr = this->current_scene_ptr;
	current_scene_ptr = next_scene_ptr;
	next_scene_ptr = nullptr;

	if (old_scene_ptr) old_scene_ptr->setWindow(std::weak_ptr<Window>());
	if (current_scene_ptr) current_scene_ptr->setWindow(this->shared_from_this());

	onSceneChanged.emit(old_scene_ptr, current_scene_ptr);
}

ScenePtr Window::getScene() const {
	return current_scene_ptr;
}

void Window::mainLoop() {
	if (current_scene_ptr != nullptr)
		current_scene_ptr->onRefreshBuffers.emit();

	std::lock_guard<std::mutex> guard(rendering);

	// Sprawdzanie wielkosci okna
	{
		//https://www.glfw.org/docs/latest/window_guide.html#window_size
		glfwGetWindowSize(glfw_window,
						  &window_width,
						  &window_height);
		glfwGetWindowFrameSize(glfw_window,
							   &window_left_offset,
							   &window_top_offset,
							   &window_right_offset,
							   &win_bottom_offset);;
	}

	// teoretycznie można by zrobić jakieś niebo ale to zbyteczne na obecną chwilę
	glClearColor(0.564705882f, 0.752941176f, 0.91372549f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//https://stackoverflow.com/questions/7240747/how-to-draw-2d-3d-stuffs-in-opengl-together

	if (current_scene_ptr != nullptr) {
		auto ptr = this->shared_from_this();
		current_scene_ptr->render(ptr);
	}

	glfwSwapBuffers(glfw_window);

	glfwPollEvents();
	if (current_scene_ptr != nullptr) {
		auto current_input_interface_wptr = current_scene_ptr->getInputInterface();

		if (lastInputInterface.lock().get() == current_input_interface_wptr.get())
			current_input_interface_wptr->updateState(glfw_window);
		else
			current_input_interface_wptr->initState(glfw_window);

		lastInputInterface = current_input_interface_wptr;
	}

	if (current_scene_ptr != nullptr)
		current_scene_ptr->pollEvents();
}

GLFWwindow *Window::getGlfwWindow() const {
	return glfw_window;
}


int Window::getWinWidth() const {
	return window_width;
}

int Window::getWinHeight() const {
	return window_height;
}

int Window::getWinTopOffset() const {
	return window_top_offset;
}

int Window::getWinLeftOffset() const {
	return window_left_offset;
}

int Window::getWinRightOffset() const {
	return window_right_offset;
}

int Window::getWinBottomOffset() const {
	return win_bottom_offset;
}

ViewPort Window::getViewPort() const {
	return viewPort;
}

void Window::setViewPort(ViewPort viewPort) {
	Window::viewPort = viewPort;

	switch (viewPort) {
		case OneTwoOne:
			glViewport(window_left_offset, win_bottom_offset, window_width, window_height);
			break;
		case Square:
			auto size = std::min(window_width, window_height);
			glViewport((window_width - size) / 2, (window_height - size) / 2, size, size);
			break;
	}
}

glm::vec2 Window::scalePixelPosToViewPortPos(ViewPort viewPort, glm::vec2 pos) {
	if (window_width > window_height) {
		pos.x -= float(window_width - window_height) / 2;
		pos /= window_height;
	} else {
		pos.y -= float(window_height - window_width) / 2;
		pos /= window_width;
	}
	return pos;
}

void Window::close() {
	onClosing();
	glfwSetWindowShouldClose(glfw_window, true);
}
