#include "scene.h"
#include "point.h"
#include "inputInterface.h"

using namespace engine;

Scene::Scene() {
}

WindowWPtr Scene::getWindow() const {
	return window;
}

void Scene::setWindow(WindowWPtr window) {
	Scene::window = window;
	onWindowChanged.emit();
}

InputInterfacePtr Scene::getInputInterface() {
	return this->inputInterface;
}

void Scene::setInputInterface(InputInterfacePtr interfacePtr) {
//	if (this->inputInterface)
//		this->inputInterface->unattachFromScene();

	this->inputInterface = interfacePtr;

//	if (this->inputInterface != nullptr)
//		this->inputInterface->attachToScene(this->shared_from_this());
}

bool Scene::isInWindow() {
	return window.expired();
}