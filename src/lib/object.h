#pragma once

#include <list>
#include "src/_classdef.h"
#include "signal.h"

class Object {
private:
	Object *parent = nullptr;
	std::list<Object *> childrens;
public:
	explicit Object(Object *parent = nullptr);
	~Object();

	Object *getParent() const;
	void setParent(Object *parent);

	Signal<Object*> onDestroy;
};