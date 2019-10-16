#pragma once

#include "_classdef.h"

#include "Light.h"
#include "Shader.h"
#include "Window.h"

namespace gengine {

	class Scene {

	protected:
		Light* light;
		Shader* shader;

	public:

		virtual void render3D(Window *window) = 0;
		virtual void renderGUI(Window *window) = 0;

		const Light& getLight() const{
			return *light;
		}

		const Shader& getShader() const{
			return *shader;
		}
	};
}
