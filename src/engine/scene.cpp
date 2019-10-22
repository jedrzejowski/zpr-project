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

Keyboard *Scene::getKeyboard() const {
	return keyboard;
}

void Scene::setKeyboard(Keyboard *keyboard) {
	Scene::keyboard = keyboard;
}

void Scene::setMouse(Mouse *mouse) {
	Scene::mouse = mouse;
}

Mouse *Scene::getMouse() const {
	return mouse;
}