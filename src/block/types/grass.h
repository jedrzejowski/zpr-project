#pragma once

#include "src/_classdef.h"
#include "../solidblock.h"

namespace block {
	class Grass : public SolidBlock {
	public:
		Grass();
		int typeId() override;
	};
}

