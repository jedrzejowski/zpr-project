#include "window.h"

#include <mutex>
#include "src/exception.h"
#include "inputInterface.h"

using namespace engine;


Window::Window() {
}

void Window::open() {

	if (glfwInit() != GL_TRUE)
		throw exception("GLFW initialization failed");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef DARWIN
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	glfwWin = glfwCreateWindow(winWidth, winHeight, getTitle().c_str(), nullptr, nullptr);

	if (glfwWin == nullptr)
		throw exception("Can't open GLFW window");

	glfwMakeContextCurrent(glfwWin);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw exception("GLEW initialization failed");

	glEnable(GL_DEPTH_TEST);

//	vsync
//	glfwSwapInterval(0);

//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	initObjects();

	while (!glfwWindowShouldClose(glfwWin)) {
		mainLoop();
	}

	glfwTerminate();
}

Scene *Window::setScene(Scene *scene) {
	std::lock_guard<std::mutex> guard(rendering);

	auto oldScene = this->currentScene;
	currentScene = scene;

	currentScene->setWindow(this);
	onSceneChanged.emit(oldScene, currentScene);

	return oldScene;
}

Scene *Window::getScene() const {
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
						  &winWidth,
						  &winHeight);
		glfwGetWindowFrameSize(glfwWin,
							   &winLeftOffset,
							   &winTopOffset,
							   &winRightOffset,
							   &winBottomOffset);;
	}

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//https://stackoverflow.com/questions/7240747/how-to-draw-2d-3d-stuffs-in-opengl-together

	if (currentScene != nullptr) {

		currentScene->render(this);

		auto currentInputInterface = currentScene->getInputInterface();

		if (currentInputInterface != nullptr) {
			if (lastInputInterface == currentInputInterface)
				currentInputInterface->updateState(glfwWin);
			else currentInputInterface->initState(glfwWin);
		}

		lastInputInterface = currentInputInterface;
	}

	glfwSwapBuffers(glfwWin);
	glfwPollEvents();
}

GLFWwindow *Window::getGlfwWindow() const {
	return glfwWin;
}


int Window::getWinWidth() const {
	return winWidth;
}

int Window::getWinHeight() const {
	return winHeight;
}

int Window::getWinTopOffset() const {
	return winTopOffset;
}

int Window::getWinLeftOffset() const {
	return winLeftOffset;
}

int Window::getWinRightOffset() const {
	return winRightOffset;
}

int Window::getWinBottomOffset() const {
	return winBottomOffset;
}

ViewPort Window::getViewPort() const {
	return viewPort;
}

void Window::setViewPort(ViewPort viewPort) {
	Window::viewPort = viewPort;

	switch (viewPort) {
		case OneTwoOne:
			glViewport(winLeftOffset, winBottomOffset, winWidth, winHeight);
			break;
		case Square:
			auto size = std::min(winWidth, winHeight);
			glViewport((winWidth - size) / 2, (winHeight - size) / 2, size, size);
			break;
	}
}

glm::vec2 Window::scalePixelPosToViewPortPos(ViewPort viewPort, glm::vec2 pos) {
	if (winWidth > winHeight) {
		pos.x -= float(winWidth - winHeight) / 2;
		pos /= winHeight;
	} else {
		pos.y -= float(winHeight - winWidth) / 2;
		pos /= winWidth;
	}
	return pos;
}
