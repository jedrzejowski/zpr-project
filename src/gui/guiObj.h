#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"
#include "src/engine/Engine.h"

namespace gui {
	class GuiObject : public Object {
	protected:
		glm::mat4 model = glm::mat4(1);
	public:

		explicit GuiObject(Object *parent = nullptr);

		virtual void insertToBuffers(std::vector<engine::Point3DeX> &vertices,
									 std::vector<engine::SimpleTriangle> &indices) = 0;


		void insertSquareToBuffers(
				float x, float y,
				float width, float height,
				float textureX, float textureY,
				float textureWidth, float textureHeight,
				std::vector<engine::Point3DeX> &vertices,
				std::vector<engine::SimpleTriangle> &indices);

		const glm::mat4 &getModel() const;
		void setModel(const glm::mat4 &model);
	};
}


