#include "button.h"
#include "src/lib/object.h"

gui::Button::Button(Interface *interface) :
		RectangleObj(interface) {
	setSize(glm::vec3(1, 0.13, 0));
	setState(Idle);
}

const std::string &gui::Button::getLabel() const {
	return label;
}

void gui::Button::setLabel(const std::string &label) {
	Button::label = label;
}

gui::ButtonState gui::Button::getState() const {
	return state;
}

void gui::Button::setState(gui::ButtonState state) {
	Button::state = state;

	switch (state) {
		case Idle:
			setTexture(
					glm::vec2(0, 1/3.f),
					glm::vec2(1, 2 / 3.f)
			);
			break;
		case Hover:
			setTexture(
					glm::vec2(0, 2 / 3.f),
					glm::vec2(1, 1)
			);
			break;
		case Clicked:
			setTexture(
					glm::vec2(0, 0),
					glm::vec2(1, 1 / 3.f)
			);
			break;
		case Disabled:
			setTexture(
					glm::vec2(0, 0),
					glm::vec2(1, 1 / 3.f)
			);
			break;
	}
}
