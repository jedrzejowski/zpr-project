#include "inputDevice.h"
#include "inputInterface.h"
#include "scene.h"

engine::InputDevice::InputDevice(engine::InputInterface *ii) :
		Object(ii) {
}

GLFWwindow *engine::InputDevice::getGLFWwindow() {
	auto *scene = inputInterface->getScene();
	if (scene == nullptr) return nullptr;
	auto *window = scene->getWindow();
	if (window == nullptr) return nullptr;
	return window->getGlfwWindow();
}
