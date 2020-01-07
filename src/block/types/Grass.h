/**
 * @file Grass.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/block/Solidblock.h"

namespace block {
	class Grass : public SolidBlock {
	public:
		Grass();
		int typeId() override;
	};
}

