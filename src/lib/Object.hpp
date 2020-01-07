/**
 * @file Object.hpp
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <list>
#include <functional>
#include <map>

#include "src/_classdef.h"


template<typename... Args>
class Signal {
	typedef std::function<void(Args...)> Func;
	struct Slot {
		bool hasPointer = false;
		const ObjectWPtr inst;
		std::function<void(Args...)> func;
	};

private:
	mutable std::map<int, Slot> slots;
	mutable int currentId = 0;

public:
	Signal() = default;
	~Signal() {
		disconnectAll();
	}

	int connect(const ObjectWPtr inst, const Func &func) const {
		slots.insert(std::make_pair(++currentId, Slot{true, inst, func}));
		return currentId;
	}

	int connect(const Func &func) const {
		slots.insert(std::make_pair(++currentId, Slot{false, ObjectWPtr(), func}));
		return currentId;
	}

	void disconnect(int id) const {
		slots.erase(id);
	}

	void disconnectAll() const {
		while (slots.size() > 0)
			disconnect(slots.begin()->first);
	}

	void emit(Args... p) const {
		for (const auto &it : slots) {

			if (it.second.hasPointer == false || !it.second.inst.expired())
				it.second.func(std::forward<Args>(p)...);
		}
	}

	void operator()(const ObjectWPtr inst, const Func &func) const {
		connect(inst, func);
	}

	void operator()(const Func &func) const {
		connect(func);
	}

	void operator()(Args... p) const {
		emit(p...);
	}

	Signal(const Signal &) = delete;
	void operator=(const Signal &) = delete;
	Signal(const Signal &&) = delete;
	void operator=(const Signal &&) = delete;
};


class Object {
public:
	explicit Object();
	virtual ~Object();

	Object(const Object &) = delete;
	void operator=(const Object &) = delete;
	Object(const Object &&) = delete;
	void operator=(const Object &&) = delete;
};



// Orginalna funkcja znajduje się tu
// https://schneegans.github.io/tutorials/2015/09/20/signal-slot
