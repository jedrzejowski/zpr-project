/**
 * @file Dirt.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/block/Solidblock.h"

namespace block {
	class Dirt : public SolidBlock {
	public:
		Dirt();
		int typeId() override;
	};
}
