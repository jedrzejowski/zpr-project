#pragma once

#include "src/_classdef.h"

// Orginalna funkcja znajduje się tu
// https://schneegans.github.io/tutorials/2015/09/20/signal-slot

#include <functional>
#include <map>

// A signal object may call multiple slots with the
// same signature. You can connect functions to the signal
// which will be called when the emit() method on the
// signal object is invoked. Any argument passed to emit()
// will be passed to the given functions.

template<typename... Args>
class Signal {
private:
	mutable std::map<int, std::function<void(Args...)>> slots;
	mutable int currentId;
public:

	Signal() : currentId(0) {}

	// copy creates new signal
	Signal(Signal const &other) : currentId(0) {}

	// connects a member function to this Signal
	template<typename T>
	int connect(T *inst, void (T::*func)(Args...)) {
		auto id = connect([=](Args... args) {
			(inst->*func)(args...);
		});

		inst->onDestroy.connect([this, id](Object *obj) {
			this->disconnect(id);
		});

		return id;
	}

	// connects a const member function to this Signal
	template<typename T>
	int connect(T *inst, void (T::*func)(Args...) const) {
		auto id = connect([=](Args... args) {
			(inst->*func)(args...);
		});

		inst->onDestroy.connect([this, id](Object *obj) {
			this->disconnect(id);
		});

		return id;
	}

	// connects a std::function to the signal. The returned
	// value can be used to disconnect the function again
	int connect(std::function<void(Args...)> const &slot) const {
		slots.insert(std::make_pair(++currentId, slot));
		return currentId;
	}

	// disconnects a previously connected function
	void disconnect(int id) const {
		slots.erase(id);
	}

	// disconnects all previously connected functions
	void disconnectAll() const {
		slots.clear();
	}

	// calls all connected functions
	void emit(Args... p) {
		for (auto const &it : slots) {
			it.second(std::forward<Args>(p)...);
		}
	}

	// assignment creates new Signal
	Signal &operator=(Signal const &other) {
		disconnectAll();
	}
};
