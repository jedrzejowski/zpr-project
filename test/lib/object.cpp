#include "src/lib/Object.hpp"

std::list<Object *> listOfObjects;

Object *createObject(Object* parent = nullptr) {
	auto object = new Object();

	listOfObjects.push_back(object);

	object->onDestroy([](Object *object) {
		listOfObjects.remove(object);
	});

	return object;
}

int main() {
	auto obj1 = createObject();

	{
		auto obj2 = createObject(obj1);
		auto obj3 = createObject(obj1);

		auto obj4 = createObject(obj2);
		auto obj5 = createObject(obj3);
		auto obj6 = createObject(obj3);
		auto obj7 = createObject(obj3);
	}

	delete(obj1);

	return listOfObjects.size();
}