/**
 * @file PlayerItem.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "PlayerItem.h"

#include "Player.h"
#include "PlayerInterface.h"
#include "src/gui/Interface.h"
#include "src/block/Solidblock.h"
#include "src/map/World.h"
#include "src/map/Chunk.h"
#include "src/block/Factory.h"

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
		solid_block_ptr(block),
		block_ptr(block) {
	logger(4).constructor(this);
}

game::PlayerSolidBlockItem::~PlayerSolidBlockItem() {
	logger(4).destructor(this);
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

	vertices_buffer.clear();
	indices_buffer.clear();

	auto vOffest = indices_buffer.size();

	auto &topTex = solid_block_ptr->getTopTextureReference();
	auto &sideTex = solid_block_ptr->getSideTextureReference();

	{ // Góra
		auto point_xy = getModel() * glm::vec4(0, 0, 0, 1);
		auto point_Xy = getModel() * glm::vec4(-1, -0.5, 0, 1);
		auto point_XY = getModel() * glm::vec4(0, -1, 0, 1);
		auto point_xY = getModel() * glm::vec4(1, -0.5, 0, 1);

		vertices_buffer.emplace_back(point_xy, topTex.getTexCoord_xy());
		vertices_buffer.emplace_back(point_Xy, topTex.getTexCoord_Xy());
		vertices_buffer.emplace_back(point_XY, topTex.getTexCoord_XY());
		vertices_buffer.emplace_back(point_xY, topTex.getTexCoord_xY());

		indices_buffer.emplace_back(engine::EboTriangle(0, 2, 1) + vOffest);
		indices_buffer.emplace_back(engine::EboTriangle(0, 3, 2) + vOffest);

		vOffest += 4;
	}

	{ // Lewo
		auto point_xy = getModel() * glm::vec4(0, 0, 0, 1);
		auto point_Xy = getModel() * glm::vec4(0, 1, 0, 1);
		auto point_XY = getModel() * glm::vec4(-1, 0.5, 0, 1);
		auto point_xY = getModel() * glm::vec4(-1, -0.5, 0, 1);

		vertices_buffer.emplace_back(point_xy, sideTex.getTexCoord_xY());
		vertices_buffer.emplace_back(point_Xy, sideTex.getTexCoord_xy());
		vertices_buffer.emplace_back(point_XY, sideTex.getTexCoord_Xy());
		vertices_buffer.emplace_back(point_xY, sideTex.getTexCoord_XY());

		indices_buffer.emplace_back(engine::EboTriangle(0, 2, 1) + vOffest);
		indices_buffer.emplace_back(engine::EboTriangle(0, 3, 2) + vOffest);

		vOffest += 4;
	}

	{ // Prawo
		auto point_xy = getModel() * glm::vec4(0, 0, 0, 1);
		auto point_Xy = getModel() * glm::vec4(1, -0.5, 0, 1);
		auto point_XY = getModel() * glm::vec4(1, 0.5, 0, 1);
		auto point_xY = getModel() * glm::vec4(0, 1, 0, 1);

		vertices_buffer.emplace_back(point_xy, sideTex.getTexCoord_xy());
		vertices_buffer.emplace_back(point_Xy, sideTex.getTexCoord_Xy());
		vertices_buffer.emplace_back(point_XY, sideTex.getTexCoord_XY());
		vertices_buffer.emplace_back(point_xY, sideTex.getTexCoord_xY());

		indices_buffer.emplace_back(engine::EboTriangle(0, 2, 1) + vOffest);
		indices_buffer.emplace_back(engine::EboTriangle(0, 3, 2) + vOffest);

		vOffest += 4;
	}

	setNeedRefreshBuffers(false);
}

void game::PlayerSolidBlockItem::useItem(map::WorldPtr &worldMap, game::PlayerPtr &player) {
	if (!player->isPointingBlock()) return;
	try {

		auto new_position = player->getNewBlockPosition();

		if (auto chunk = worldMap->getChunk(new_position.getChunkCoord()).lock()) {
			auto new_block = block::Factory::clone(block_ptr);
			chunk->setBlock(new_position.getBlockCoord(), new_block);
		}
	} catch (WrongJsonException &exception) {
		logger(0).err("Error during block placing.").log("Mostly likely somethiung is not implemented ...");
	} catch (std::exception &exception) {
		logger(0).err("Fatal error during block placing.").log("Can't place block");
	}
}
