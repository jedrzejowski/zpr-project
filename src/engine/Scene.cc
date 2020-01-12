/**
 * @file Scene.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Scene.h"
#include "Point.hpp"
#include "InputInterface.h"


engine::Scene::Scene() {
}

engine::WindowWPtr engine::Scene::getWindow() const {
	return window_wptr;
}

void engine::Scene::setWindow(WindowWPtr window) {
	Scene::window_wptr = window;
	onWindowChanged.emit();
}

engine::InputInterfacePtr engine::Scene::getInputInterface() {
	return this->input_interface_ptr;
}

void engine::Scene::setInputInterface(InputInterfacePtr interface_ptr) {
	if (this->input_interface_ptr)
		this->input_interface_ptr->unattachFromScene();

	this->input_interface_ptr = std::move(interface_ptr);

	if (this->input_interface_ptr != nullptr) {
		auto tmp = shared_from_this();
		this->input_interface_ptr->attachToScene(tmp);
	}
}

bool engine::Scene::isInWindow() {
	return window_wptr.expired();
}
