/**
 * @file FpsCounter.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "FpsCounter.h"
#include "src/OpenGL.h"

engine::FpsCounter::FpsCounter() {
}

void engine::FpsCounter::tickFrame() {
	fifo.push(glfwGetTime());

	if (fifo.size() > maxSize)
		fifo.pop();
}

float engine::FpsCounter::getNowFPS() {
	return fifo.back() / 1000;
}
