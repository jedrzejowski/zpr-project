/**
 * @file Factory.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "_classdef.h"
#include "lib/json.hpp"
using json = nlohmann::json;

namespace block {
	class Factory {
	public:
		static BlockPtr create(json& data);
		static BlockPtr clone(BlockPtr& block);
	};
}


