#include "scene.h"
#include "point.h"
#include "inputInterface.h"

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
	return this->inputInterface;
}

void Scene::setInputInterface(InputInterface *inputInterface) {
	if (this->inputInterface != nullptr)
		this->inputInterface->unattachedFromScene(this);

	this->inputInterface = inputInterface;

	if (this->inputInterface != nullptr)
		this->inputInterface->attachedToScene(this);
}
