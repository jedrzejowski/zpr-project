/**
 * @file Scene.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Scene.h"
#include "Point.hpp"
#include "InputInterface.h"

using namespace engine;

Scene::Scene() {
}

WindowWPtr Scene::getWindow() const {
	return window_wptr;
}

void Scene::setWindow(WindowWPtr window) {
	Scene::window_wptr = window;
	onWindowChanged.emit();
}

InputInterfacePtr Scene::getInputInterface() {
	return this->input_interface_ptr;
}

void Scene::setInputInterface(InputInterfacePtr interface_ptr) {
	if (this->input_interface_ptr)
		this->input_interface_ptr->unattachFromScene();

	this->input_interface_ptr = std::move(interface_ptr);

	if (this->input_interface_ptr != nullptr)
		this->input_interface_ptr->attachToScene(this->shared_from_this());
}

bool Scene::isInWindow() {
	return window_wptr.expired();
}
