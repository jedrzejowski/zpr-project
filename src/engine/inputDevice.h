#pragma once

#include "src/opengl.h"
#include "src/_classdef.h"
#include "src/lib/object.h"

namespace engine {

	class InputDevice : public Object {
		friend InputInterface;
	private:
		InputInterface *inputInterface;

		void _updateState(GLFWwindow *window);

	protected:

		virtual void updateState(GLFWwindow *window) = 0;
		virtual void initState(GLFWwindow *window) = 0;

	public:
		explicit InputDevice(InputInterface *ii);
	};
}

