/**
 * @file Shader.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <src/_classdef.h>
#include "ShaderProgram.h"

namespace engine {

	class Shader {
	protected:
		ShaderProgram program;
	public:
		Shader(const std::string &vertexPath, const std::string &fragmentPath);
		[[nodiscard]] const ShaderProgram& getProgram() const;

		virtual void bind();
		virtual void unbind();
	};
}