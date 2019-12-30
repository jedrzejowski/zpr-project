#include "scene.h"
#include "point.h"
#include "inputInterface.h"

using namespace engine;

Scene::Scene() {
}

Window *Scene::getWindow() const {
	return window;
}

void Scene::setWindow(Window *window) {
	Scene::window = window;
	setParent(window);
	onWindowChanged.emit();
}

InputInterfacePtr Scene::getInputInterface() {
	return this->inputInterface;
}

void Scene::setInputInterface(InputInterfacePtr interfacePtr) {
	if (this->inputInterface != nullptr)
		this->inputInterface->unattachFromScene();

	this->inputInterface = interfacePtr;

	if (this->inputInterface != nullptr)
		this->inputInterface->attachToScene(this);
}

bool Scene::isInWindow() {
	return window == nullptr;
}