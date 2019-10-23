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
	private:
		std::mutex rendering;

		int winWidth = 800, winHeight = 600, winTopOffset, winLeftOffset, winRightOffset, winBottomOffset;

		GLFWwindow *glfwWin;

		Scene *currentScene = nullptr;

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
		int getSceneWidth() const;
		int getSceneHeight() const;
		int getWinWidth() const;
		int getWinHeight() const;
		int getWinTopOffset() const;
		int getWinLeftOffset() const;
		int getWinRightOffset() const;
		int getWinBottomOffset() const;
	};
}
