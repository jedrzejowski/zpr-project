#pragma once

#include <algorithm>

template<typename T>
inline T clip(const T &lower, const T &n, const T &upper) {
	return std::max(lower, std::min(n, upper));
}