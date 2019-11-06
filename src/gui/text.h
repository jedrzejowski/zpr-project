#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"

namespace gui {

	class Text : public Object {
	private:
		glm::mat4 model = glm::mat4(1);
		std::string content;

	public:
		explicit Text(Object* parent = nullptr);

		virtual void insertToBuffers(std::vector<engine::Point3DeX> &vertices,
									 std::vector<engine::SimpleTriangle> &indices) = 0;


		const glm::mat4 &getModel() const;
		void setModel(const glm::mat4 &model);

		const std::string &getContent() const;
		void setContent(const std::string &content);
	};
}

