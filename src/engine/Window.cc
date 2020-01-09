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

	if (glfwInit() != GL_TRUE)
		throw zprException("Window::open", "GLFW initialization failed");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef DARWIN
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	glfwWin = glfwCreateWindow(window_width, window_height, getTitle().c_str(), nullptr, nullptr);

	if (glfwWin == nullptr)
		throw zprException("Window::open", "Can't open GLFW window");

	glfwMakeContextCurrent(glfwWin);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw zprException("Window::open", "GLEW initialization failed");

	glEnable(GL_DEPTH_TEST);

//	vsync
//	glfwSwapInterval(0);

//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	initObjects();

	double lastTime = -1, nowTime = 0;
	while (!glfwWindowShouldClose(glfwWin)) {

		lastTime = nowTime;
		nowTime = glfwGetTime();
		auto delta = nowTime - lastTime;

//		logger(1).log("fps").log(1 / delta);

		mainLoop();
		swapScene();
	}

	glfwTerminate();
}

void Window::setScene(ScenePtr scene) {
	nextScene = scene;
	//TODO dodać zwracanie wyjątku kiedy jest już jakaś scena w kolejce
}

void Window::swapScene() {
	if (nextScene == nullptr) return;

	auto oldScene = this->currentScene;
	currentScene = nextScene;
	nextScene = nullptr;

	if (oldScene) oldScene->setWindow(std::weak_ptr<Window>());
	if (currentScene) currentScene->setWindow(this->shared_from_this());

	onSceneChanged.emit(oldScene, currentScene);
}

ScenePtr Window::getScene() const {
	return currentScene;
}

void Window::mainLoop() {
	if (currentScene != nullptr)
		currentScene->onRefreshBuffers.emit();

	std::lock_guard<std::mutex> guard(rendering);

	// Sprawdzanie wielkosci okna
	{
		//https://www.glfw.org/docs/latest/window_guide.html#window_size
		glfwGetWindowSize(glfwWin,
						  &window_width,
						  &window_height);
		glfwGetWindowFrameSize(glfwWin,
							   &window_left_offset,
							   &window_top_offset,
							   &window_right_offset,
							   &win_bottom_offset);;
	}

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//https://stackoverflow.com/questions/7240747/how-to-draw-2d-3d-stuffs-in-opengl-together

	if (currentScene != nullptr) {
		auto ptr = this->shared_from_this();
		currentScene->render(ptr);
	}

	glfwSwapBuffers(glfwWin);

	glfwPollEvents();
	if (currentScene != nullptr) {
		auto currentInputInterface = currentScene->getInputInterface();

		if (lastInputInterface.lock().get() == currentInputInterface.get())
			currentInputInterface->updateState(glfwWin);
		else
			currentInputInterface->initState(glfwWin);

		lastInputInterface = currentInputInterface;
	}

	if (currentScene != nullptr)
		currentScene->pollEvents();
}

GLFWwindow *Window::getGlfwWindow() const {
	return glfwWin;
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
