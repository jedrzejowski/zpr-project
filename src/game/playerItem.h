#pragma once

#include "_classdef.h"
#include "src/lib/object.h"
#include "src/opengl.h"
#include "src/gui/guiObj.h"

namespace game {
	class PlayerItem : public gui::GuiObject {
		PlayerInterfaceWPtr playerInterface;
		glm::vec2 textureStart{}, textureEnd{};
		uint32_t textureNo{};

	protected:
		void setTextureStart(const glm::vec2 &textureStart);
		void setTextureEnd(const glm::vec2 &textureEnd);
		void setTextureNo(uint32_t textureNo);

	public:
		explicit PlayerItem(PlayerInterfacePtr playerInterfacePtr);

		const glm::vec2 &getTextureStart() const;
		const glm::vec2 &getTextureEnd() const;
		uint32_t getTextureNo() const;
		const PlayerInterfaceWPtr &getPlayerInterface() const;

		virtual void useItem(map::WorldPtr &worldMap, PlayerPtr &player) = 0;
	};

	class PlayerBlockItem : public PlayerItem {
		block::BlockPtr& block;
	public:
		PlayerBlockItem(PlayerInterfacePtr playerInterfacePtr, block::BlockPtr& block);
		void useItem(map::WorldPtr &worldMap, PlayerPtr &player) override;
	};
}
