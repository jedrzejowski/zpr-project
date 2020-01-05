#pragma once

#include "src/_classdef.h"
#include "../solidblock.h"

namespace block {
	class Water : public SolidBlock {
	public:
		Water();
		int typeId() override;
	};
}

