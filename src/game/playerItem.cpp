//
// Created by adam on 06.01.2020.
//

#include "playerItem.h"
#include "playerInterface.h"
#include "src/gui/interface.h"

game::PlayerItem::PlayerItem(game::PlayerInterfacePtr playerInterfacePtr) :
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


game::PlayerBlockItem::PlayerBlockItem(game::PlayerInterfacePtr playerInterfacePtr, block::BlockPtr &block) :
		PlayerItem(playerInterfacePtr),
		block(block) {
}

void game::PlayerBlockItem::useItem(map::WorldPtr &worldMap, game::PlayerPtr &player) {
}
