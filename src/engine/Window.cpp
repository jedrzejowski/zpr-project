//
// Created by adam on 23.04.18.
//

#include <mutex>
#include "exception.h"
#include "Window.h"

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

	glfwWin = glfwCreateWindow(width, height, getTitle().c_str(), nullptr, nullptr);

	if (glfwWin == nullptr)
		throw exception("Can't open GLFW window");

	glfwMakeContextCurrent(glfwWin);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw exception("GLEW initialization failed");

	glViewport(0, 0, width, height);
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
	return oldScene;
}

void Window::mainLoop() {
	std::lock_guard<std::mutex> guard(rendering);

	currentFrame = (float) glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	glViewport(0, 0, width, height);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//https://stackoverflow.com/questions/7240747/how-to-draw-2d-3d-stuffs-in-opengl-together

	if (currentScene != nullptr) {

		// Renderowanie sceny
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
//	glFrustum(-aspect * near / lens, aspect * near / lens, -near / lens, near / lens, near, far);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		this->currentScene->render3D(this);
//
//	// Renderowanie interfejsu użytkownika
//	glClear(GL_DEPTH_BUFFER_BIT);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(0, width, 0, height, 0, 1);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	this->currentScene->renderGUI(this);
	}

	glfwSwapBuffers(glfwWin);
	glfwPollEvents();
}
