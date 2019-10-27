#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"
#include "src/engine/Engine.h"

namespace gui {
	class GuiObject : public Object {
	private:
		glm::mat4 model = glm::mat4(1);
	public:

		explicit GuiObject(Object *parent = nullptr);

		virtual void insertToBuffers(std::vector<engine::Point3DeX> &vertices,
									 std::vector<engine::SimpleTriangle> &indices) = 0;

		virtual bool isCollisionWithMouse(const glm::vec2& mousePosition) = 0;

		const glm::mat4 &getModel() const;
		void setModel(const glm::mat4 &model);

		const Signal<const glm::vec2 &> onHover;
		const Signal<const glm::vec2 &> onPressed;
		const Signal<const glm::vec2 &> onReleased;
	};
}


