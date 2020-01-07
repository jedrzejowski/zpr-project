/**
 * @file RectangleObj.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/lib/Object.hpp"
#include "GuiObject.h"
#include "src/engine/TextureReference.h"

namespace gui {

	class RectangleObj : public GuiObject, public VirtualSharePtrObject<RectangleObj> {
	private:

		glm::vec2 position = glm::vec2(0);
		glm::vec2 size = glm::vec2(1);

		glm::vec3 point_xy,
				point_Xy,
				point_xY,
				point_XY;

		engine::SquareTextureReference textureReference;

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

		const engine::SquareTextureReference &getTextureReference() const;
		void setTextureReference(const engine::SquareTextureReference &textureReference);
	};
}

