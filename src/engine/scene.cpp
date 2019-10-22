//
// Created by adam on 14.04.18.
//

#include "point3D.h"

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
