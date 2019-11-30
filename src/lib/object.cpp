#include <sstream>
#include "object.h"

Object::Object(Object *parent) {
	setParent(parent);
}

Object::~Object() {
	onDestroy.emit(this);

	for (auto child : childrens)
		delete (child);
}

Object *Object::getParent() const {
	return parent;
}

void Object::setParent(Object *newParent) {
	if (newParent != nullptr)
		logger.warn("ustawienie rodzica");


	if (this->parent != nullptr)
		this->parent->childrens.remove(this);
	this->parent = newParent;
	if (this->parent != nullptr)
		this->parent->childrens.push_back(this);
}

const std::list<Object *> &Object::getChildrens() const {
	return childrens;
}

void dumpTreeLine(std::stringstream &output, std::string prefix, Object *object) {

	output << prefix << object << std::endl;
	prefix += "    ";
	for (auto child : object->getChildrens())
		dumpTreeLine(output, prefix, child);
}

void Object::dumpParentTree() {
	std::stringstream output;

	dumpTreeLine(output, "", this);

	logger.log("Dump of object").log(this).enter().log(output.rdbuf());
}

