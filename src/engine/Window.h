#pragma once

#include <mutex>

#include "src/_classdef.h"
#include "src/lib/Object.hpp"

#include "Camera.h"
#include "Scene.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace engine {
	enum ViewPort {
		OneTwoOne,
		Square,
	};

	class Window : public Object, public virtual_enable_shared_from_this<Window> {
	private:
		std::mutex rendering;

		int winWidth = 800, winHeight = 600,
				winTopOffset = 0, winLeftOffset = 0,
				winRightOffset = 0, winBottomOffset = 0;

		GLFWwindow *glfwWin = nullptr;
		ScenePtr currentScene;
		ScenePtr nextScene;
		ViewPort viewPort;
		InputInterfaceWPtr lastInputInterface;

		void mainLoop();
		void swapScene();
	public:
		Window();

		virtual void initObjects() = 0;

		void open();

		void setScene(ScenePtr scene);
		ScenePtr getScene() const;
		const Signal<ScenePtr, ScenePtr> onSceneChanged;

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
		glm::vec2 scalePixelPosToViewPortPos(ViewPort viewPort, glm::vec2 pos);
	};
}
