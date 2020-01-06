#include "solidblock.h"
#include "src/engine/Engine.h"
#include "wall.h"


block::SolidBlock::SolidBlock(const Coord2D &top,
							  const Coord2D &side,
							  const Coord2D &bottom
) : texTop(getBlockTexture(top.x, top.y)),
	texSide(getBlockTexture(side.x, side.y)),
	texBottom(getBlockTexture(bottom.x, bottom.y)) {
}


void block::SolidBlock::insertToBuffers(std::vector<engine::Point3DeX> &vertices,
										std::vector<engine::SimpleTriangle> &indices) {
	BlockPtr block;

	auto vOffest = vertices.size();
	auto iOffest = indices.size();


	// płaszczna Z
	if (!(block = this->getNeighbor(0, 0, +1).lock()) || !block->isSolid()) {
		auto wall = getWall(position, Direction::Z_PLUS);

		vertices.emplace_back(engine::Point3D(wall.firstPoint), texTop.getTexCoord_xy());
		vertices.emplace_back(engine::Point3D(wall.secondPoint), texTop.getTexCoord_Xy());
		vertices.emplace_back(engine::Point3D(wall.thirdPoint), texTop.getTexCoord_XY());
		vertices.emplace_back(engine::Point3D(wall.fourthPoint), texTop.getTexCoord_xY());

		indices.push_back(engine::SimpleTriangle(1, 3, 2) - 1 + vOffest);
		indices.push_back(engine::SimpleTriangle(1, 4, 3) - 1 + vOffest);

		vOffest += 4;
	}

	// płaszczna z

	if (!(block = this->getNeighbor(0, 0, -1).lock()) || !block->isSolid()) {
		auto wall = getWall(position, Direction::Z_MINUS);

		vertices.emplace_back(engine::Point3D(wall.firstPoint), texBottom.getTexCoord_xy());
		vertices.emplace_back(engine::Point3D(wall.secondPoint), texBottom.getTexCoord_Xy());
		vertices.emplace_back(engine::Point3D(wall.thirdPoint), texBottom.getTexCoord_XY());
		vertices.emplace_back(engine::Point3D(wall.fourthPoint), texBottom.getTexCoord_xY());

		indices.push_back(engine::SimpleTriangle(1, 3, 2) - 1 + vOffest);
		indices.push_back(engine::SimpleTriangle(1, 4, 3) - 1 + vOffest);

		vOffest += 4;
	}

	// płaszczna x
	if (!(block = this->getNeighbor(-1, 0, 0).lock()) || !block->isSolid()) {
		auto wall = getWall(position, Direction::X_MINUS);

		vertices.emplace_back(engine::Point3D(wall.firstPoint), texSide.getTexCoord_xy());
		vertices.emplace_back(engine::Point3D(wall.secondPoint), texSide.getTexCoord_Xy());
		vertices.emplace_back(engine::Point3D(wall.thirdPoint), texSide.getTexCoord_XY());
		vertices.emplace_back(engine::Point3D(wall.fourthPoint), texSide.getTexCoord_xY());

		indices.push_back(engine::SimpleTriangle(1, 3, 2) - 1 + vOffest);
		indices.push_back(engine::SimpleTriangle(1, 4, 3) - 1 + vOffest);

		vOffest += 4;
	}

	// płaszczna X
	if (!(block = this->getNeighbor(+1, 0, 0).lock()) || !block->isSolid()) {
		auto wall = getWall(position, Direction::X_PLUS);

		vertices.emplace_back(engine::Point3D(wall.firstPoint), texSide.getTexCoord_xy());
		vertices.emplace_back(engine::Point3D(wall.secondPoint), texSide.getTexCoord_Xy());
		vertices.emplace_back(engine::Point3D(wall.thirdPoint), texSide.getTexCoord_XY());
		vertices.emplace_back(engine::Point3D(wall.fourthPoint), texSide.getTexCoord_xY());

		indices.push_back(engine::SimpleTriangle(1, 3, 2) - 1 + vOffest);
		indices.push_back(engine::SimpleTriangle(1, 4, 3) - 1 + vOffest);

		vOffest += 4;
	}

	// płaszczna y
	if (!(block = this->getNeighbor(0, -1, 0).lock()) || !block->isSolid()) {
		auto wall = getWall(position, Direction::Y_MINUS);

		vertices.emplace_back(engine::Point3D(wall.firstPoint), texSide.getTexCoord_xy());
		vertices.emplace_back(engine::Point3D(wall.secondPoint), texSide.getTexCoord_Xy());
		vertices.emplace_back(engine::Point3D(wall.thirdPoint), texSide.getTexCoord_XY());
		vertices.emplace_back(engine::Point3D(wall.fourthPoint), texSide.getTexCoord_xY());

		indices.push_back(engine::SimpleTriangle(1, 3, 2) - 1 + vOffest);
		indices.push_back(engine::SimpleTriangle(1, 4, 3) - 1 + vOffest);

		vOffest += 4;
	}

	// płaszczna Y
	if (!(block = this->getNeighbor(0, +1, 0).lock()) || !block->isSolid()) {
		auto wall = getWall(position, Direction::Y_PLUS);

		vertices.emplace_back(engine::Point3D(wall.firstPoint), texSide.getTexCoord_xy());
		vertices.emplace_back(engine::Point3D(wall.secondPoint), texSide.getTexCoord_Xy());
		vertices.emplace_back(engine::Point3D(wall.thirdPoint), texSide.getTexCoord_XY());
		vertices.emplace_back(engine::Point3D(wall.fourthPoint), texSide.getTexCoord_xY());

		indices.push_back(engine::SimpleTriangle(1, 3, 2) - 1 + vOffest);
		indices.push_back(engine::SimpleTriangle(1, 4, 3) - 1 + vOffest);

		vOffest += 4;
	}
}
