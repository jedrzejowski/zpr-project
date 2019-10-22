#pragma once

#include <mutex>

#include "src/_classdef.h"
#include "src/lib/object.h"

#include "camera.h"
#include "scene.h"
#include "keyboard.h"
#include "mouse.h"

namespace engine {
	class Window : public Object {
	protected:
		std::mutex rendering;

		int width = 800, height = 600;
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
		Scene *getScene() const;
		const Signal<Scene *, Scene *> onSceneChanged;

		virtual std::string getTitle() = 0;

		GLFWwindow *getGlfwWindow() const;
		GLuint getWidth() const;
		GLuint getHeight() const;
	};
}
