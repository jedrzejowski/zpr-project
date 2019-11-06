#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"
#include "guiObj.h"

namespace gui {

	class RectangleObj : public GuiObject {
	private:

		glm::vec2 position = glm::vec2(0);
		glm::vec2 size = glm::vec2(1);

		glm::vec3 point_xy,
				point_Xy,
				point_xY,
				point_XY;

		glm::vec2 textureStart, textureEnd;

		bool wasMouseIn = false;

		void refreshModel();

	public:

		explicit RectangleObj(Interface *interface);

		bool isCollisionWithMouse(const glm::vec2 &mousePosition);
		void updateBuffers() override;

		const glm::vec2 &getPosition() const;
		void setPosition(const glm::vec2 &position);
		const glm::vec2 &getSize() const;
		void setSize(const glm::vec2 &size);


		const glm::vec2 &getTextureStart() const;
		void setTextureStart(const glm::vec2 &textureStart);
		const glm::vec2 &getTextureEnd() const;
		void setTextureEnd(const glm::vec2 &textureEnd);
		void setTexture(const glm::vec2 &textureStart, const glm::vec2 &textureEnd);
	};
}

