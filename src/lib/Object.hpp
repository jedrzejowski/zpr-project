/**
 * @file Object.hpp
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once


#include "src/_classdef.h"


class Object : public VirtualSharePtrObject<Object> {
public:
	explicit Object();
	virtual ~Object();

	Object(const Object &) = delete;
	void operator=(const Object &) = delete;
	Object(const Object &&) = delete;
	void operator=(const Object &&) = delete;
};
