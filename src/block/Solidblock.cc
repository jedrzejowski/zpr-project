/**
 * @file Solidblock.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Solidblock.h"
#include "src/engine/Engine.h"
#include "Wall.h"


block::SolidBlock::SolidBlock(json &data) : Block(data) {
}


void block::SolidBlock::initTextureReferences() const {
	auto top = getTopTextureCoord();
	auto side = getSideTextureCoord();
	auto bottom = getBottomTextureCoord();

	texture_top = getBlockTexture(top.x, top.y);
	texture_side = getBlockTexture(side.x, side.y);
	texture_bottom = getBlockTexture(bottom.x, bottom.y);

	is_texture_reference_init_required = false;
}


void block::SolidBlock::insertToBuffers(std::vector<engine::Point3DeX> &vertices,
										std::vector<engine::EboTriangle> &indices) {

	if (is_texture_reference_init_required)
		initTextureReferences();

	BlockPtr block;

	auto vOffest = vertices.size();
	auto iOffest = indices.size();


	// płaszczna Z
	if (!(block = this->getNeighbor(0, 0, +1).lock()) || !block->isSolid()) {
		auto wall = getWall(position, Direction::Z_PLUS);

		vertices.emplace_back(engine::Point3D(wall.first_point), texture_top.getTexCoord_XY());
		vertices.emplace_back(engine::Point3D(wall.second_point), texture_top.getTexCoord_Xy());
		vertices.emplace_back(engine::Point3D(wall.third_point), texture_top.getTexCoord_xy());
		vertices.emplace_back(engine::Point3D(wall.fourth_point), texture_top.getTexCoord_xY());

		indices.push_back(engine::EboTriangle(1, 3, 2) - 1 + vOffest);
		indices.push_back(engine::EboTriangle(1, 4, 3) - 1 + vOffest);

		vOffest += 4;
	}

	// płaszczna z

	if (!(block = this->getNeighbor(0, 0, -1).lock()) || !block->isSolid()) {
		auto wall = getWall(position, Direction::Z_MINUS);

		vertices.emplace_back(engine::Point3D(wall.first_point), texture_bottom.getTexCoord_xy());
		vertices.emplace_back(engine::Point3D(wall.second_point), texture_bottom.getTexCoord_Xy());
		vertices.emplace_back(engine::Point3D(wall.third_point), texture_bottom.getTexCoord_XY());
		vertices.emplace_back(engine::Point3D(wall.fourth_point), texture_bottom.getTexCoord_xY());

		indices.push_back(engine::EboTriangle(1, 3, 2) - 1 + vOffest);
		indices.push_back(engine::EboTriangle(1, 4, 3) - 1 + vOffest);

		vOffest += 4;
	}

	// płaszczna x
	if (!(block = this->getNeighbor(-1, 0, 0).lock()) || !block->isSolid()) {
		auto wall = getWall(position, Direction::X_MINUS);

		vertices.emplace_back(engine::Point3D(wall.first_point), texture_side.getTexCoord_XY());
		vertices.emplace_back(engine::Point3D(wall.second_point), texture_side.getTexCoord_xY());
		vertices.emplace_back(engine::Point3D(wall.third_point), texture_side.getTexCoord_xy());
		vertices.emplace_back(engine::Point3D(wall.fourth_point), texture_side.getTexCoord_Xy());

		indices.push_back(engine::EboTriangle(1, 3, 2) - 1 + vOffest);
		indices.push_back(engine::EboTriangle(1, 4, 3) - 1 + vOffest);

		vOffest += 4;
	}

	// płaszczna X
	if (!(block = this->getNeighbor(+1, 0, 0).lock()) || !block->isSolid()) {
		auto wall = getWall(position, Direction::X_PLUS);

		vertices.emplace_back(engine::Point3D(wall.first_point), texture_side.getTexCoord_xY());
		vertices.emplace_back(engine::Point3D(wall.second_point), texture_side.getTexCoord_xy());
		vertices.emplace_back(engine::Point3D(wall.third_point), texture_side.getTexCoord_Xy());
		vertices.emplace_back(engine::Point3D(wall.fourth_point), texture_side.getTexCoord_XY());

		indices.push_back(engine::EboTriangle(1, 3, 2) - 1 + vOffest);
		indices.push_back(engine::EboTriangle(1, 4, 3) - 1 + vOffest);

		vOffest += 4;
	}

	// płaszczna y
	if (!(block = this->getNeighbor(0, -1, 0).lock()) || !block->isSolid()) {
		auto wall = getWall(position, Direction::Y_MINUS);

		vertices.emplace_back(engine::Point3D(wall.first_point), texture_side.getTexCoord_xY());
		vertices.emplace_back(engine::Point3D(wall.second_point), texture_side.getTexCoord_xy());
		vertices.emplace_back(engine::Point3D(wall.third_point), texture_side.getTexCoord_Xy());
		vertices.emplace_back(engine::Point3D(wall.fourth_point), texture_side.getTexCoord_XY());

		indices.push_back(engine::EboTriangle(1, 3, 2) - 1 + vOffest);
		indices.push_back(engine::EboTriangle(1, 4, 3) - 1 + vOffest);

		vOffest += 4;
	}

	// płaszczna Y
	if (!(block = this->getNeighbor(0, +1, 0).lock()) || !block->isSolid()) {
		auto wall = getWall(position, Direction::Y_PLUS);

		vertices.emplace_back(engine::Point3D(wall.first_point), texture_side.getTexCoord_XY());
		vertices.emplace_back(engine::Point3D(wall.second_point), texture_side.getTexCoord_xY());
		vertices.emplace_back(engine::Point3D(wall.third_point), texture_side.getTexCoord_xy());
		vertices.emplace_back(engine::Point3D(wall.fourth_point), texture_side.getTexCoord_Xy());

		indices.push_back(engine::EboTriangle(1, 3, 2) - 1 + vOffest);
		indices.push_back(engine::EboTriangle(1, 4, 3) - 1 + vOffest);

		vOffest += 4;
	}
}

const engine::SquareTextureReference &block::SolidBlock::getTopTextureReference() const {
	if (is_texture_reference_init_required)
		initTextureReferences();

	return texture_top;
}

const engine::SquareTextureReference &block::SolidBlock::getSideTextureReference() const {
	if (is_texture_reference_init_required)
		initTextureReferences();

	return texture_side;
}

const engine::SquareTextureReference &block::SolidBlock::getBottomTextureReference() const {
	if (is_texture_reference_init_required)
		initTextureReferences();

	return texture_bottom;
}

bool block::SolidBlock::isTextureReferenceInitRequired() const {
	return is_texture_reference_init_required;
}

void block::SolidBlock::setIsTextureReferenceInitRequired(bool isTextureReferenceInitRequired) {
	is_texture_reference_init_required = isTextureReferenceInitRequired;
}
