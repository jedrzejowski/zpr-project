#pragma once

#include "src/_classdef.h"

#include "Light.h"
#include "Shader.h"
#include "Window.h"

namespace engine {

	class Scene {

	protected:

	public:

		virtual void render3D(Window *window) = 0;
		virtual void renderGUI(Window *window) = 0;

	};
}
