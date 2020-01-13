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
	/**
	 * @brief Fabryka bloków
	 */
	class Factory {
	public:

		/**
		 * @brief Tworzy block z obiektu json
		 * @param data
		 * @return
		 */
		static BlockPtr create(json& data);

		/**
		 * @brief Klonowanie bloku
		 * @param block
		 * @return
		 */
		static BlockPtr clone(BlockPtr& block);
	};
}


