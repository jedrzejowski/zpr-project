//
// Created by adam on 14.04.18.
//

#include "point.h"

#include "scene.h"

using namespace engine;

Window *Scene::getWindow() const {
	return window;
}

void Scene::setWindow(Window *window) {
	Scene::window = window;
	setParent(window);
	onWindowChanged.emit();
}

InputInterface *Scene::getInputInterface() const {
	return inputInterface;
}

void Scene::setInputInterface(InputInterface *inputInterface) {
	Scene::inputInterface = inputInterface;
}
