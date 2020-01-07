#include "Solidblock.h"
#include "src/engine/Engine.h"
#include "Wall.h"


block::SolidBlock::SolidBlock(const Coord2D &top,
							  const Coord2D &side,
							  const Coord2D &bottom
) : texture_top(getBlockTexture(top.x, top.y)),
	texture_side(getBlockTexture(side.x, side.y)),
	texture_bottom(getBlockTexture(bottom.x, bottom.y)) {
}


void block::SolidBlock::insertToBuffers(std::vector<engine::Point3DeX> &vertices,
										std::vector<engine::EboTriangle> &indices) {
	BlockPtr block;

	auto vOffest = vertices.size();
	auto iOffest = indices.size();


	// płaszczna Z
	if (!(block = this->getNeighbor(0, 0, +1).lock()) || !block->isSolid()) {
		auto wall = getWall(position, Direction::Z_PLUS);

		vertices.emplace_back(engine::Point3D(wall.firstPoint), texture_top.getTexCoord_xy());
		vertices.emplace_back(engine::Point3D(wall.secondPoint), texture_top.getTexCoord_Xy());
		vertices.emplace_back(engine::Point3D(wall.thirdPoint), texture_top.getTexCoord_XY());
		vertices.emplace_back(engine::Point3D(wall.fourthPoint), texture_top.getTexCoord_xY());

		indices.push_back(engine::EboTriangle(1, 3, 2) - 1 + vOffest);
		indices.push_back(engine::EboTriangle(1, 4, 3) - 1 + vOffest);

		vOffest += 4;
	}

	// płaszczna z

	if (!(block = this->getNeighbor(0, 0, -1).lock()) || !block->isSolid()) {
		auto wall = getWall(position, Direction::Z_MINUS);

		vertices.emplace_back(engine::Point3D(wall.firstPoint), texture_bottom.getTexCoord_xy());
		vertices.emplace_back(engine::Point3D(wall.secondPoint), texture_bottom.getTexCoord_Xy());
		vertices.emplace_back(engine::Point3D(wall.thirdPoint), texture_bottom.getTexCoord_XY());
		vertices.emplace_back(engine::Point3D(wall.fourthPoint), texture_bottom.getTexCoord_xY());

		indices.push_back(engine::EboTriangle(1, 3, 2) - 1 + vOffest);
		indices.push_back(engine::EboTriangle(1, 4, 3) - 1 + vOffest);

		vOffest += 4;
	}

	// płaszczna x
	if (!(block = this->getNeighbor(-1, 0, 0).lock()) || !block->isSolid()) {
		auto wall = getWall(position, Direction::X_MINUS);

		vertices.emplace_back(engine::Point3D(wall.firstPoint), texture_side.getTexCoord_xy());
		vertices.emplace_back(engine::Point3D(wall.secondPoint), texture_side.getTexCoord_Xy());
		vertices.emplace_back(engine::Point3D(wall.thirdPoint), texture_side.getTexCoord_XY());
		vertices.emplace_back(engine::Point3D(wall.fourthPoint), texture_side.getTexCoord_xY());

		indices.push_back(engine::EboTriangle(1, 3, 2) - 1 + vOffest);
		indices.push_back(engine::EboTriangle(1, 4, 3) - 1 + vOffest);

		vOffest += 4;
	}

	// płaszczna X
	if (!(block = this->getNeighbor(+1, 0, 0).lock()) || !block->isSolid()) {
		auto wall = getWall(position, Direction::X_PLUS);

		vertices.emplace_back(engine::Point3D(wall.firstPoint), texture_side.getTexCoord_xy());
		vertices.emplace_back(engine::Point3D(wall.secondPoint), texture_side.getTexCoord_xY());
		vertices.emplace_back(engine::Point3D(wall.thirdPoint), texture_side.getTexCoord_XY());
		vertices.emplace_back(engine::Point3D(wall.fourthPoint), texture_side.getTexCoord_Xy());

		indices.push_back(engine::EboTriangle(1, 3, 2) - 1 + vOffest);
		indices.push_back(engine::EboTriangle(1, 4, 3) - 1 + vOffest);

		vOffest += 4;
	}

	// płaszczna y
	if (!(block = this->getNeighbor(0, -1, 0).lock()) || !block->isSolid()) {
		auto wall = getWall(position, Direction::Y_MINUS);

		vertices.emplace_back(engine::Point3D(wall.firstPoint), texture_side.getTexCoord_xy());
		vertices.emplace_back(engine::Point3D(wall.secondPoint), texture_side.getTexCoord_xY());
		vertices.emplace_back(engine::Point3D(wall.thirdPoint), texture_side.getTexCoord_XY());
		vertices.emplace_back(engine::Point3D(wall.fourthPoint), texture_side.getTexCoord_Xy());

		indices.push_back(engine::EboTriangle(1, 3, 2) - 1 + vOffest);
		indices.push_back(engine::EboTriangle(1, 4, 3) - 1 + vOffest);

		vOffest += 4;
	}

	// płaszczna Y
	if (!(block = this->getNeighbor(0, +1, 0).lock()) || !block->isSolid()) {
		auto wall = getWall(position, Direction::Y_PLUS);

		vertices.emplace_back(engine::Point3D(wall.firstPoint), texture_side.getTexCoord_xy());
		vertices.emplace_back(engine::Point3D(wall.secondPoint), texture_side.getTexCoord_Xy());
		vertices.emplace_back(engine::Point3D(wall.thirdPoint), texture_side.getTexCoord_XY());
		vertices.emplace_back(engine::Point3D(wall.fourthPoint), texture_side.getTexCoord_xY());

		indices.push_back(engine::EboTriangle(1, 3, 2) - 1 + vOffest);
		indices.push_back(engine::EboTriangle(1, 4, 3) - 1 + vOffest);

		vOffest += 4;
	}
}

const engine::SquareTextureReference &block::SolidBlock::getTextureTop() const {
	return texture_top;
}

const engine::SquareTextureReference &block::SolidBlock::getTextureSide() const {
	return texture_side;
}

const engine::SquareTextureReference &block::SolidBlock::getTextureBottom() const {
	return texture_bottom;
}
