#pragma once

#include <queue>
#include "src/_classdef.h"
#include "src/lib/object.h"

namespace engine {
	class FpsCounter : public Object {
		std::queue<double> fifo;

		int maxSize = 100;
	public:
		FpsCounter(Object *parent = nullptr);

		void tickFrame();

		float getNowFPS();
	};
}

