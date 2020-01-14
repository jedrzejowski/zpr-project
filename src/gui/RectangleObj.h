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

	/**
	 * @brief Prosty obiekt prostokąta z obsługą myszy
	 */
	class RectangleObj : public GuiObject, public VirtualSharePtrObject<RectangleObj> {
	public:
		using VirtualSharePtrObject<RectangleObj>::shared_from_this;
		using VirtualSharePtrObject<RectangleObj>::weak_from_this;
	private:

		glm::vec2 position = glm::vec2(0);
		glm::vec2 size = glm::vec2(1);

		glm::vec3 point_xy,
				point_Xy,
				point_xY,
				point_XY;

		engine::SquareTextureReference texture_reference;

		bool is_mouse_in = false;

		void refreshModel();

	protected:

		void constructorRectangleObj();

	public:

		explicit RectangleObj(InterfacePtr interface);
		explicit RectangleObj(GuiObjectPtr gui_object);

		bool isCollisionWithMouse(const glm::vec2 &mousePosition);
		void updateBuffers() override;

		const glm::vec2 &getPosition() const;
		void setPosition(const glm::vec2 &new_position);
		const glm::vec2 &getSize() const;
		void setSize(const glm::vec2 &new_size);

		virtual glm::vec2 getBaseSize() {
			return glm::vec2(1, 1);
		}

		const engine::SquareTextureReference &getTextureReference() const;
		void setTextureReference(const engine::SquareTextureReference &textureReference);

		const Signal<const glm::vec2&, const glm::vec2&> onSizeChanged;
		const Signal<const glm::vec2&, const glm::vec2&> onPositionChanged;
	};
}

