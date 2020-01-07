/**
 * @file VirtualSharePtrObject.hpp
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

//https://stackoverflow.com/questions/15549722/double-inheritance-of-enable-shared-from-this

#include <memory>

struct virtual_enable_shared_from_this_base :
		std::enable_shared_from_this<virtual_enable_shared_from_this_base> {
	virtual ~virtual_enable_shared_from_this_base() {}
};

template<typename T>
struct VirtualSharePtrObject : virtual virtual_enable_shared_from_this_base {
	std::shared_ptr<T> shared_from_this() {
		return std::dynamic_pointer_cast<T>(virtual_enable_shared_from_this_base::shared_from_this());
	}
};