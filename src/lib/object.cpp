#include <sstream>
#include "object.h"

Object::Object(Object *parent) {
	setParent(parent);
}

Object::~Object() {

	for (auto &obj : childrens)
		delete (obj);

	setParent(nullptr);

	onDestroy.emit(this);
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

void Object::dumpParentTree() {
	std::stringstream output;



	logger.log("Dump of object").log(this).enter().log(output);
}