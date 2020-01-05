//
// Created by adam on 05.01.2020.
//

#include "shader.h"

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
