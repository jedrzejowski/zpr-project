//
// Created by adam on 06.01.2020.
//

#include "playerItem.h"

#include "playerInterface.h"
#include "src/gui/interface.h"
#include "src/block/solidblock.h"

game::PlayerItem::PlayerItem(const game::PlayerInterfacePtr &playerInterfacePtr) :
		gui::GuiObject(std::static_pointer_cast<gui::Interface>(playerInterfacePtr)),
		playerInterface(playerInterfacePtr) {
}

const glm::vec2 &game::PlayerItem::getTextureStart() const {
	return textureStart;
}

void game::PlayerItem::setTextureStart(const glm::vec2 &textureStart) {
	PlayerItem::textureStart = textureStart;
}

const glm::vec2 &game::PlayerItem::getTextureEnd() const {
	return textureEnd;
}

void game::PlayerItem::setTextureEnd(const glm::vec2 &textureEnd) {
	PlayerItem::textureEnd = textureEnd;
}

uint32_t game::PlayerItem::getTextureNo() const {
	return textureNo;
}

void game::PlayerItem::setTextureNo(uint32_t textureNo) {
	PlayerItem::textureNo = textureNo;
}

const game::PlayerInterfaceWPtr &game::PlayerItem::getPlayerInterface() const {
	return playerInterface;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


game::PlayerSolidBlockItem::PlayerSolidBlockItem(game::PlayerInterfacePtr &playerInterfacePtr,
												 block::SolidBlockPtr &block) :
		PlayerItem(playerInterfacePtr),
		block(block) {
	logger.constructor(this);
}

game::PlayerSolidBlockItem::~PlayerSolidBlockItem() {
	logger.destructor(this);
}

game::PlayerBlockItemPtr
game::PlayerSolidBlockItem::create(PlayerInterfacePtr &playerInterfacePtr, block::SolidBlockPtr &block) {
	struct Self : PlayerSolidBlockItem {
		Self(PlayerInterfacePtr &playerInterfacePtr, block::SolidBlockPtr &block) :
				PlayerSolidBlockItem(playerInterfacePtr, block) {}
	};

	auto self = std::make_shared<Self>(playerInterfacePtr, block);

	return self;
}

void game::PlayerSolidBlockItem::updateBuffers() {

	verticesBuf.clear();
	indicesBuf.clear();

	auto vOffest = indicesBuf.size();

	auto &topTex = block->getTextureTop();
	auto &sideTex = block->getTextureSide();

	{ // Góra
		auto point_xy = getModel() * glm::vec4(0, 0, 0, 1);
		auto point_Xy = getModel() * glm::vec4(-1, -0.5, 0, 1);
		auto point_XY = getModel() * glm::vec4(0, -1, 0, 1);
		auto point_xY = getModel() * glm::vec4(1, -0.5, 0, 1);

		verticesBuf.emplace_back(point_xy, topTex.getTexCoord_xy());
		verticesBuf.emplace_back(point_Xy, topTex.getTexCoord_Xy());
		verticesBuf.emplace_back(point_XY, topTex.getTexCoord_XY());
		verticesBuf.emplace_back(point_xY, topTex.getTexCoord_xY());

		indicesBuf.emplace_back(engine::SimpleTriangle(0, 2, 1) + vOffest);
		indicesBuf.emplace_back(engine::SimpleTriangle(0, 3, 2) + vOffest);

		vOffest += 4;
	}

	{ // Lewo
		auto point_xy = getModel() * glm::vec4(0, 0, 0, 1);
		auto point_Xy = getModel() * glm::vec4(0, 1, 0, 1);
		auto point_XY = getModel() * glm::vec4(-1, 0.5, 0, 1);
		auto point_xY = getModel() * glm::vec4(-1, -0.5, 0, 1);

		verticesBuf.emplace_back(point_xy, sideTex.getTexCoord_xy());
		verticesBuf.emplace_back(point_Xy, sideTex.getTexCoord_Xy());
		verticesBuf.emplace_back(point_XY, sideTex.getTexCoord_XY());
		verticesBuf.emplace_back(point_xY, sideTex.getTexCoord_xY());

		indicesBuf.emplace_back(engine::SimpleTriangle(0, 2, 1) + vOffest);
		indicesBuf.emplace_back(engine::SimpleTriangle(0, 3, 2) + vOffest);

		vOffest += 4;
	}

	{ // Prawo
		auto point_xy = getModel() * glm::vec4(0, 0, 0, 1);
		auto point_Xy = getModel() * glm::vec4(1, -0.5, 0, 1);
		auto point_XY = getModel() * glm::vec4(1, 0.5, 0, 1);
		auto point_xY = getModel() * glm::vec4(0, 1, 0, 1);

		verticesBuf.emplace_back(point_xy, sideTex.getTexCoord_xy());
		verticesBuf.emplace_back(point_Xy, sideTex.getTexCoord_Xy());
		verticesBuf.emplace_back(point_XY, sideTex.getTexCoord_XY());
		verticesBuf.emplace_back(point_xY, sideTex.getTexCoord_xY());

		indicesBuf.emplace_back(engine::SimpleTriangle(0, 2, 1) + vOffest);
		indicesBuf.emplace_back(engine::SimpleTriangle(0, 3, 2) + vOffest);

		vOffest += 4;
	}
}

void game::PlayerSolidBlockItem::useItem(map::WorldPtr &worldMap, game::PlayerPtr &player) {
}
