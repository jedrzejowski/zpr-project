#pragma once

#include "src/_classdef.h"
#include "src/lib/coord.h"

namespace block {

	class Block : public virtual_enable_shared_from_this<Block> {
	protected:
		map::ChunkWPtr chunk;
		Coord3D position;

	public:
		static const float TexColumns;
		static const float TexRows;
		static std::tuple<glm::vec2, glm::vec2> getBlockText(int x, int y);

		Block();
		~Block() override;

		void setPosition(map::ChunkPtr &chunkPtr, const Coord3D &pos);

		virtual void insertToBuffers(std::vector<engine::Point3DeX> &vertices,
									 std::vector<engine::SimpleTriangle> &indices) = 0;

		virtual bool isSolid();

		virtual json toJSON();

		virtual int typeId() = 0;

		BlockWPtr getNeighbor(CoordDim dx, CoordDim dy, CoordDim dz) const;
	};

	extern const BlockWPtr Air;
}

