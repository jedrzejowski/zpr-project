//
// Created by adam on 23.04.18.
//

#include <src/exception.h>
#include "Window.h"

using namespace gengine;

void Window::open() {

	if (glfwInit() != GL_TRUE)
		throw gkom::exception("GLFW initialization failed");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef DARWIN
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	glfwWin = glfwCreateWindow(WIDTH, HEIGHT, getTitle().c_str(), nullptr, nullptr);

	if (glfwWin == nullptr)
		throw gkom::exception("Can't open GLFW window");

	glfwMakeContextCurrent(glfwWin);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw gkom::exception("GLEW initialization failed");

	glViewport(0, 0, WIDTH, HEIGHT);
	glEnable(GL_DEPTH_TEST);

//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	initObjects();

	while (!glfwWindowShouldClose(glfwWin)) {
		currentFrame = (float) glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		keyCallback(glfwWin);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		windowLoop();

		glfwSwapBuffers(glfwWin);
		glfwPollEvents();
	}


	glfwTerminate();
}
