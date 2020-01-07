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
		explicit PlayerItem(const PlayerInterfacePtr &playerInterfacePtr);

		const glm::vec2 &getTextureStart() const;
		const glm::vec2 &getTextureEnd() const;
		uint32_t getTextureNo() const;
		const PlayerInterfaceWPtr &getPlayerInterface() const;

		virtual void useItem(map::WorldPtr &worldMap, PlayerPtr &player) = 0;
	};

	class PlayerSolidBlockItem : public PlayerItem, public virtual_enable_shared_from_this<PlayerSolidBlockItem> {
		block::SolidBlockPtr block;
		PlayerSolidBlockItem(PlayerInterfacePtr &playerInterfacePtr, block::SolidBlockPtr &block);
	public:
		~PlayerSolidBlockItem();
		static PlayerBlockItemPtr create(PlayerInterfacePtr &playerInterfacePtr, block::SolidBlockPtr& block);
		void updateBuffers() override;
		void useItem(map::WorldPtr &worldMap, PlayerPtr &player) override;

	};
}
