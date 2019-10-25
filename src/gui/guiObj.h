#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"
#include "src/engine/Engine.h"

namespace gui {
	class GuiObject : public Object {
	protected:
		glm::vec3 position;
	public:

		explicit GuiObject(Interface* parent = nullptr);

		virtual void insertToBuffers(std::vector<engine::Point3DeX> &vertices,
									 std::vector<engine::SimpleTriangle> &indices) = 0;

		const glm::vec3 &getPosition() const;
		void setPosition(const glm::vec3 &postion);
	};
}


