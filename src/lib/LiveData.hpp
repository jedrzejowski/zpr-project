/**
 * @file LiveData.hpp
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "_classdef.h"
#include "Signal.hpp"

template<typename T>
class LiveData {
private:
	mutable std::mutex mutex;
	mutable T data_obj;
public:
	LiveData(T new_obj) : data_obj(new_obj) {}

	void set(T &new_obj) const {
		std::lock_guard<std::mutex> lock(mutex);

		auto old_obj = data_obj;
		data_obj = new_obj;

		onChange(old_obj, new_obj);
	}

	void set(T new_obj) const {
		std::lock_guard<std::mutex> lock(mutex);

		auto old_obj = data_obj;
		data_obj = new_obj;

		onChange(old_obj, new_obj);
	}

	[[nodiscard]] const T &get() const {
		return data_obj;
	}

	const Signal<T &, T &> onChange;
};