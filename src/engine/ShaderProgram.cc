/**
 * @file ShaderProgram.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include <src/Logger.h>
#include "src/Exception.hpp"
#include "ShaderProgram.h"
#include "Resources.h"

using namespace engine;

GLuint compileShader(const GLchar *shaderCode, GLenum shaderType) {
	GLuint shader_id = glCreateShader(shaderType);
	glShaderSource(shader_id, 1, &shaderCode, nullptr);
	glCompileShader(shader_id);

	// Print compile errors if any
	GLint success = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetShaderInfoLog(shader_id, sizeof(infoLog), nullptr, infoLog);
		std::string msg = std::string("ShaderProgram compilation: ") + infoLog;
		throw zprException("compileShader", msg);
	}
	return shader_id;
}

ShaderProgram::ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath) {
	//Vertex ShaderProgram
	std::string vertexCode = Resources::get().loadTextFile(vertexPath);
	GLuint vertexId = compileShader(vertexCode.c_str(), GL_VERTEX_SHADER);

	//FragmentShader
	std::string fragmentCode = Resources::get().loadTextFile(fragmentPath);
	GLuint fragmentId = compileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER);

	// link ShaderProgram program
	shader_id = glCreateProgram();
	glAttachShader(shader_id, vertexId);
	glAttachShader(shader_id, fragmentId);
	glLinkProgram(shader_id);


	// Print linking errors if any
	GLint success;
	glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetProgramInfoLog(shader_id, sizeof(infoLog), nullptr, infoLog);
		std::string msg = std::string("ShaderProgram program linking:\n") + infoLog;
		logger(1).info(std::string("Błąd podczas kompilacji szejdera:\n") + infoLog);
		throw zprException("ShaderProgram::ShaderProgram", msg);
	}

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(getID());
}

void ShaderProgram::bind() {
	glUseProgram(getID());
}

void ShaderProgram::unbind() {
	glUseProgram(0);
}

void ShaderProgram::setBool(const std::string &name, bool value) {
	glUniform1i(glGetUniformLocation(getID(), name.c_str()), (int) value);
}

void ShaderProgram::setInt(const std::string &name, int value) {
	glUniform1i(glGetUniformLocation(getID(), name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string &name, float value) {
	glUniform1f(glGetUniformLocation(getID(), name.c_str()), value);
}

void ShaderProgram::setVec2(const std::string &name, const glm::vec2 &value) {
	glUniform2fv(glGetUniformLocation(getID(), name.c_str()), 1, &value[0]);
}

void ShaderProgram::setVec2(const std::string &name, float x, float y) {
	glUniform2f(glGetUniformLocation(getID(), name.c_str()), x, y);
}

void ShaderProgram::setVec3(const std::string &name, const glm::vec3 &value) {
	glUniform3fv(glGetUniformLocation(getID(), name.c_str()), 1, &value[0]);
}

void ShaderProgram::setVec3(const std::string &name, float x, float y, float z) {
	glUniform3f(glGetUniformLocation(getID(), name.c_str()), x, y, z);
}

void ShaderProgram::setVec4(const std::string &name, const glm::vec4 &value) {
	glUniform4fv(glGetUniformLocation(getID(), name.c_str()), 1, &value[0]);
}

void ShaderProgram::setVec4(const std::string &name, float x, float y, float z, float w) {
	glUniform4f(glGetUniformLocation(getID(), name.c_str()), x, y, z, w);
}

void ShaderProgram::setMat2(const std::string &name, const glm::mat2 &mat) {
	glUniformMatrix2fv(glGetUniformLocation(getID(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setMat3(const std::string &name, const glm::mat3 &mat) {
	glUniformMatrix3fv(glGetUniformLocation(getID(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setMat4(const std::string &name, const glm::mat4 &mat) {
	glUniformMatrix4fv(glGetUniformLocation(getID(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setUniformNameToId(const std::string &name, int id) {
	glUniform1i(glGetUniformLocation(getID(), name.c_str()), id);
}

