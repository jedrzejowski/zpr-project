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

		virtual void bind();
		virtual void unbind();
	};
}