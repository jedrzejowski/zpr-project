#pragma once

#include <mutex>

#include "src/_classdef.h"
#include "src/lib/object.h"

#include "camera.h"
#include "scene.h"
#include "keyboard.h"
#include "mouse.h"

namespace engine {
	enum ViewPort{
		OneTwoOne,
		Square,
	};

	class Window : public Object {
	private:
		std::mutex rendering;

		int winWidth = 800, winHeight = 600,
				winTopOffset = 0, winLeftOffset = 0,
				winRightOffset = 0, winBottomOffset = 0;

		GLFWwindow *glfwWin = nullptr;
		Scene *currentScene = nullptr;
		ViewPort viewPort;

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
		int getWinWidth() const;
		int getWinHeight() const;
		int getWinTopOffset() const;
		int getWinLeftOffset() const;
		int getWinRightOffset() const;
		int getWinBottomOffset() const;

		ViewPort getViewPort() const;
		void setViewPort(ViewPort viewPort);
	};
}
