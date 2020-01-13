/**
 * @file Signal.hpp
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <list>
#include <functional>
#include <map>

#include "src/_classdef.h"
#include "Object.hpp"

/**
 * @brief Implementacja obsługi sygnałów z argumentami takimi jak w QT
 *
 * Implementuje rozchodzenie się informacji o zdarzeniach, które nastąpiło w obiekcie.
 * Do tworzenia funkcji używa wyrażeń lambda
 *
 * @see https://doc.qt.io/qt-5/signalsandslots.html
 * @tparam Args lista argumentów przesyłanych za pomocą sygnału
 */
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

			try {
				if (it.second.hasPointer == false || !it.second.inst.expired())
					it.second.func(std::forward<Args>(p)...);
			} catch (std::exception &exception) {
				logger(0).err("Error while emitting signal:").err(this).enter().err(exception.what());
			}
		}
	}

	void operator()(const ObjectWPtr inst, const Func &func) const {
		connect(inst, func);
	}

	void operator()(Object* inst, const Func &func) const {
		connect(inst->weak_from_this(), func);
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


// Orginalna funkcja znajduje się tu
// https://schneegans.github.io/tutorials/2015/09/20/signal-slot
