/**
 * @file FpsCounter.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <queue>
#include "src/_classdef.h"
#include "src/lib/Object.hpp"

namespace engine {
	class FpsCounter : public Object {
		std::queue<double> fifo;

		int maxSize = 100;
	public:
		FpsCounter();

		void tickFrame();

		float getNowFPS();
	};
}

