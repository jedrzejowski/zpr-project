//
// Created by adam on 24.10.2019.
//

#include "fpsCounter.h"
#include "src/opengl.h"

engine::FpsCounter::FpsCounter(Object *parent) :
		Object(parent) {
}

void engine::FpsCounter::tickFrame() {
	fifo.push(glfwGetTime());

	if (fifo.size() > maxSize)
		fifo.pop();
}
float engine::FpsCounter::getNowFPS() {
	return fifo.back()/1000;
}
