#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <mutex>

#include "src/_classdef.h"

#include "Camera.h"
#include "Scene.h"

namespace engine {
	class Window {
	protected:
		std::mutex rendering;

		GLuint width = 800, height = 600;
		GLFWwindow *glfwWin;
		Scene *currentScene;

		float currentFrame = 0.0f, deltaTime = 0.0f, lastFrame = 0.0f;

	private:
		void mainLoop();
	public:
		Window();

		virtual void initObjects() = 0;

		void open();

		Scene *setScene(Scene *scene);

		virtual std::string getTitle() = 0;
	};
}
