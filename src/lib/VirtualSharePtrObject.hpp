/**
 * @file VirtualSharePtrObject.hpp
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

//https://stackoverflow.com/questions/15549722/double-inheritance-of-enable-shared-from-this

#include <memory>

struct VirtualEnableSharedFromThisBase :
		std::enable_shared_from_this<VirtualEnableSharedFromThisBase> {
	virtual ~VirtualEnableSharedFromThisBase() {}
};

template<typename T>
struct VirtualSharePtrObject : virtual VirtualEnableSharedFromThisBase {
	std::shared_ptr<T> shared_from_this() {
		return std::dynamic_pointer_cast<T>(VirtualEnableSharedFromThisBase::shared_from_this());
	}

	std::weak_ptr<T> weak_from_this() {
		return std::dynamic_pointer_cast<T>(VirtualEnableSharedFromThisBase::shared_from_this());
	}
};