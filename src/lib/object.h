#pragma once

#include <list>
#include <functional>
#include <map>

#include "src/_classdef.h"

template<typename... Args>
class Signal {
	typedef std::function<void(Args...)> Slot;
	typedef std::pair<int, const Object *> RemoteSlot;
private:
	mutable std::map<int, Slot> slots;
	mutable std::map<int, RemoteSlot> remotes;
	mutable int currentId = 0;
public:
	Signal() = default;
	~Signal() {
		disconnectAll();
	}

	int connect(const Object *inst, const Slot &slot) const;

	int connect(const Slot &slot) const {
		slots.insert(std::make_pair(++currentId, slot));
		return currentId;
	}

	void disconnect(int id) const;

	void disconnectAll() const {
		while (slots.size() > 0)
			disconnect(slots.begin()->first);
	}

	void emit(Args... p) const {
		for (const auto &it : slots) {
			it.second(std::forward<Args>(p)...);
		}
	}

	void operator()(const Object *inst, const Slot &slot) const {
		connect(inst, slot);
	}

	void operator()(const Slot &slot) const {
		connect(slot);
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
private:
	Object *parent = nullptr;
	std::list<Object *> childrens;

public:
	explicit Object(Object *parent = nullptr);
	virtual ~Object();

	Object(const Object &) = delete;
	void operator=(const Object &) = delete;
	Object(const Object &&) = delete;
	void operator=(const Object &&) = delete;

	Object *getParent() const;
	void setParent(Object *parent);
	const std::list<Object *> &getChildrens() const;

	const Signal<Object *> onDestroy;

	void dumpParentTree();
};

template<typename... Args>
int Signal<Args...>::connect(const Object *inst, const Signal::Slot &slot) const {
	auto id = connect(slot);

	auto remoteId = inst->onDestroy.connect([this, id](Object *obj) {
		this->disconnect(id);
	});

	remotes.insert(std::make_pair(id, std::make_pair(remoteId, inst)));

	return id;
}

template<typename... Args>
void Signal<Args...>::disconnect(int id) const {
	slots.erase(id);
	if (remotes.count(id) > 0) {
		remotes[id].second->onDestroy.disconnect(remotes[id].first);
		remotes.erase(id);
	}
}


// Orginalna funkcja znajduje się tu
// https://schneegans.github.io/tutorials/2015/09/20/signal-slot
