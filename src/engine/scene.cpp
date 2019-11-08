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
		this->inputInterface->unattachFromScene();

	this->inputInterface = inputInterface;

	if (this->inputInterface != nullptr)
		this->inputInterface->attachToScene(this);
}

bool Scene::isInWindow() {
	return window == nullptr;
}
