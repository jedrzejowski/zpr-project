/**
 * @file LiveData.hpp
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "_classdef.h"
#include "Signal.hpp"

/**
 * @brief Klasa naśladująca LiveData z Android'a
 *
 * Klasa ma za zadzanie przechowywać proste obiekty(struktury) danych które mogą się zmieniać w czasie działania
 * aplikacji, obsługuje wielowątkowość.
 *
 * @see https://developer.android.com/topic/libraries/architecture/livedata
 * @tparam T typ wartości
 */
template<typename T>
class LiveData {
private:
	mutable std::mutex mutex;
	mutable T data_obj;
public:
	LiveData(T new_obj) : data_obj(new_obj) {}

	LiveData(const LiveData &) = delete;
	void operator=(const Object &) = delete;
	LiveData(const LiveData &&) = delete;
	void operator=(const LiveData &&) = delete;

//	void set(T &new_obj) const {
//		std::lock_guard<std::mutex> lock(mutex);
//
//		auto old_obj = data_obj;
//		data_obj = new_obj;
//
//		onChange(old_obj, new_obj);
//	}

	void set(T new_obj) const {
		std::lock_guard<std::mutex> lock(mutex);

		auto old_obj = data_obj;
		data_obj = new_obj;

		onChange(old_obj, new_obj);
	}

	[[nodiscard]] const T &get() const {
		return data_obj;
	}

	/**
	 * @brief sygnał zmiany
	 */
	const Signal<const T &, const T &> onChange;
};