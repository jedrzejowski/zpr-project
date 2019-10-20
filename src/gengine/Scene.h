#pragma once

#include "_classdef.h"

#include "Light.h"
#include "Shader.h"
#include "Window.h"

namespace gengine {

	class Scene {

	protected:

	public:

		virtual void render3D(Window *window) = 0;
		virtual void renderGUI(Window *window) = 0;

	};
}
