#include "inputDevice.h"
#include "inputInterface.h"
#include "scene.h"

engine::InputDevice::InputDevice(engine::InputInterface *ii) :
		Object(ii),
		inputInterface(ii) {
}

void engine::InputDevice::initState(GLFWwindow *window) {
	timeOfLastState = timeOfCurrentState = glfwGetTime();

	for (auto &iter : inputButtons)
		iter.second->initState(window);

	onStateChange();
}

void engine::InputDevice::updateState(GLFWwindow *window) {

	timeOfLastState = timeOfCurrentState;
	timeOfCurrentState = glfwGetTime();

	for (auto &iter : inputButtons)
		iter.second->updateState(window);

	onStateChange();
}

void engine::InputDevice::addBtn(InputButton &btn) {
	inputButtons.insert(std::pair<int, InputButton *>(btn.getBtnCode(), &btn));
}

double engine::InputDevice::getTimeOfCurrentState() const { return timeOfCurrentState; }

double engine::InputDevice::getTimeOfLastState() const { return timeOfLastState; }

double engine::InputDevice::getDeltaTimeOfState() const {
	return timeOfCurrentState - timeOfLastState;
}