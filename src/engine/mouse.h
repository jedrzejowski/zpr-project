#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"

namespace engine {
	class Mouse : public Object {
	private:
		cord2D position;
		cord2D delta;
		int mode;
	public:
		Mouse(Window* window = nullptr);

		const Signal<int, int> onMove;

	};
}

