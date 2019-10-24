#include "window.h"

#include <mutex>
#include "exception.h"
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
	std::lock_guard<std::mutex> guard(rendering);

	glViewport(0, 0, winWidth, winHeight);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//https://stackoverflow.com/questions/7240747/how-to-draw-2d-3d-stuffs-in-opengl-together

	double nowTime, lastTime;

	if (currentScene != nullptr) {

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

		// Renderowanie sceny
		currentScene->render3D(this);

		// Renderowanie interfejsu użytkownika
		glClear(GL_DEPTH_BUFFER_BIT); // Musimy wyczyścić sprawdzanie głębi ponieważ rysujemy interfejs
		this->currentScene->renderGUI(this);


		{
			auto ii = currentScene->getInputInterface();
			if (ii != nullptr) ii->updateState(glfwWin);
		}
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

int Window::getSceneWidth() const {
	return winWidth - winLeftOffset - winRightOffset;
}

int Window::getSceneHeight() const {
	return winHeight - winTopOffset - winBottomOffset;
}