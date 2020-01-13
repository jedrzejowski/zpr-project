/**
 * @file Block.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/lib/Coord.hpp"
#include "lib/json.hpp"

using json = nlohmann::json;


namespace block {

	class Block : public VirtualSharePtrObject<Block> {
	protected:
		map::ChunkWPtr chunk;
		Coord3D position;

	public:

		explicit Block() = default;
		explicit Block(json &data);
		~Block() override = default;

		void setPosition(map::ChunkPtr &chunk_ptr, const Coord3D &pos);

		virtual void insertToBuffers(std::vector<engine::Point3DeX> &vertices,
									 std::vector<engine::EboTriangle> &indices) = 0;

		virtual bool isSolid();

		virtual json toJSON();

		virtual int typeId() const = 0;

		BlockWPtr getNeighbor(CoordDim dx, CoordDim dy, CoordDim dz) const;
	};

	extern const BlockWPtr Air;
	engine::SquareTextureReference getBlockTexture(int x, int y);
}

