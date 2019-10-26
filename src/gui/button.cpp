#include "button.h"
#include "src/lib/object.h"

gui::Button::Button(Object *parent) : GuiObject(parent) {
}


void gui::Button::insertToBuffers(std::vector<engine::Point3DeX> &vertices,
								  std::vector<engine::SimpleTriangle> &indices) {

	insertSquareToBuffers(
			0, 0, 1, 1,
			0, 1 / 3.f, 1, 1 / 3.f,
			vertices, indices
	);
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
}
