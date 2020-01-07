/**
 * @file Water.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/block/Solidblock.h"

namespace block {
	class Water : public SolidBlock {
	public:
		Water();
		int typeId() override;
	};
}

