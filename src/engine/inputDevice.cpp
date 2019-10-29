#include "inputDevice.h"
#include "inputInterface.h"
#include "scene.h"

engine::InputDevice::InputDevice(engine::InputInterface *ii) :
		Object(ii),
		inputInterface(ii) {
}
