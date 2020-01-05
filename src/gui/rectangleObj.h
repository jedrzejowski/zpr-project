#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"
#include "guiObj.h"

namespace gui {

	class RectangleObj : public GuiObject, public virtual_enable_shared_from_this<RectangleObj> {
	private:

		glm::vec2 position = glm::vec2(0);
		glm::vec2 size = glm::vec2(1);

		glm::vec3 point_xy,
				point_Xy,
				point_xY,
				point_XY;

		glm::vec2 textureStart, textureEnd;
		uint32_t textureNo;

		bool isMouseIn = false;

		void refreshModel();

	protected:

		void initInputInterface();

	public:

		explicit RectangleObj(InterfacePtr interface);
		~RectangleObj();

		bool isCollisionWithMouse(const glm::vec2 &mousePosition);
		void updateBuffers() override;

		const glm::vec2 &getPosition() const;
		void setPosition(const glm::vec2 &position);
		const glm::vec2 &getSize() const;
		void setSize(const glm::vec2 &size);

		virtual glm::vec2 getBaseSize() {
			return glm::vec2(1, 1);
		}

		const glm::vec2 &getTextureStart() const;
		void setTextureStart(const glm::vec2 &textureStart);
		const glm::vec2 &getTextureEnd() const;
		void setTextureEnd(const glm::vec2 &textureEnd);
		uint32_t getTextureNo() const;
		void setTextureNo(uint32_t textureNo);
		void setTexture(const glm::vec2 &textureStart, const glm::vec2 &textureEnd, uint32_t textureNo = 0);
	};
}

