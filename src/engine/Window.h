/**
 * @file Window.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

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

	class Window : public Object, public VirtualSharePtrObject<Window> {
	private:
		std::mutex rendering;

		int window_width = 800, window_height = 600,
				window_top_offset = 0, window_left_offset = 0,
				window_right_offset = 0, win_bottom_offset = 0;

		GLFWwindow *glfw_window = nullptr;
		ScenePtr current_scene_ptr;
		ScenePtr next_scene_ptr;
		ViewPort viewPort;
		InputInterfaceWPtr last_input_interface_wptr;

		void mainLoop();
		void swapScene();
	public:
		Window();

		virtual void initObjects() = 0;

		void open();
		void close();

		const Signal<> onOpening;
		const Signal<> onOpened;
		const Signal<> onClosing;
		const Signal<> onClosed;

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
