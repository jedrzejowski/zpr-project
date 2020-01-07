#pragma once

#include "src/_classdef.h"
#include "src/block/Solidblock.h"

namespace block {
	class Stone : public SolidBlock {
	public:
		Stone();
		int typeId() override;
	};
}

