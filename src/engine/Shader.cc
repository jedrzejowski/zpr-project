/**
 * @file Shader.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Shader.h"

engine::Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) :
		program(vertexPath, fragmentPath) {
}

const engine::ShaderProgram &engine::Shader::getProgram() const {
	return program;
}

void engine::Shader::bind() {
	program.bind();
}

void engine::Shader::unbind() {
	program.unbind();
}
