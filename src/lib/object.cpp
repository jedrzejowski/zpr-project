#include "object.h"

Object::Object(Object *parent) {
	setParent(parent);
}

Object::~Object() {

	onDestroy.emit(this);

	for (const auto &obj:childrens)
		delete (obj);

	if (parent != nullptr)
		parent->childrens.remove(this);
}

Object *Object::getParent() const {
	return parent;
}

void Object::setParent(Object *newParent) {
	if (this->parent != nullptr)
		this->parent->childrens.remove(this);
	this->parent = newParent;
	if (this->parent != nullptr)
		this->parent->childrens.push_back(this);
}
