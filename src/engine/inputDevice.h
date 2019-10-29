#pragma once

#include "src/opengl.h"
#include "src/_classdef.h"
#include "src/lib/object.h"


namespace engine {
	class InputDevice : public Object {
		friend InputInterface;
	private:
		InputInterface *inputInterface;

		virtual void updateState() = 0;

	protected:
		GLFWwindow *getGLFWwindow();

	public:
		explicit InputDevice(InputInterface *ii);

	};
}

