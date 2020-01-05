#pragma once

#include <src/_classdef.h>
#include "shaderProgram.h"

namespace engine {

	class Shader {
	protected:
		ShaderProgram program;
	public:
		Shader(const std::string &vertexPath, const std::string &fragmentPath);
		const ShaderProgram& getProgram() const;

		virtual glm::vec2 getPointInWindow(const glm::vec3& vec) = 0;

		void bind();
		void unbind();
	};
}