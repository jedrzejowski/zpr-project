#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"
#include "guiObj.h"

namespace gui {

	class RectangleObj : public GuiObject {
	private:
		glm::vec3 position = glm::vec3(0);
		glm::vec3 size = glm::vec3(1);

		glm::vec3 point_xy,
				point_Xy,
				point_xY,
				point_XY;

		glm::vec2 textureStart, textureEnd;
	public:

		explicit RectangleObj(Interface *interface);

		void insertToBuffers(std::vector<engine::Point3DeX> &vertices,
							 std::vector<engine::SimpleTriangle> &indices) override;

		bool isCollisionWithMouse(const engine::Mouse* mouse) override;

		const glm::vec3 &getPosition() const;
		void setPosition(const glm::vec3 &position);
		const glm::vec3 &getSize() const;
		void setSize(const glm::vec3 &size);

		const glm::vec2 &getTextureStart() const;
		void setTextureStart(const glm::vec2 &textureStart);
		const glm::vec2 &getTextureEnd() const;
		void setTextureEnd(const glm::vec2 &textureEnd);
		void setTexture(const glm::vec2 &textureStart, const glm::vec2 &textureEnd);
	};
}

