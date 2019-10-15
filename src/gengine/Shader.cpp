//
// Created by adam on 07.04.18.
//

#include "src/FileSystem.h"
#include "exception.h"
#include "Shader.h"

using namespace gengine;

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
		std::string msg = std::string("Shader compilation: ") + infoLog;
		throw exception(msg);
	}
	return shader_id;
}

Shader::Shader(std::string vertexPath, std::string fragmentPath) {
	//Vertex Shader
	vertexPath.insert(0, "../shaders/vertex/");
	vertexPath.append(".vert");
	std::string vertexCode = gkom::FileSystem::loadTextFile(vertexPath);
	GLuint vertexId = compileShader(vertexCode.c_str(), GL_VERTEX_SHADER);


	//FragmentShader
	fragmentPath.insert(0, "../shaders/fragment/");
	fragmentPath.append(".frag");
	std::string fragmentCode = gkom::FileSystem::loadTextFile(fragmentPath);
	GLuint fragmentId = compileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER);

	// link Shader program
	shaderId = glCreateProgram();
	glAttachShader(shaderId, vertexId);
	glAttachShader(shaderId, fragmentId);
	glLinkProgram(shaderId);

	// Print linking errors if any
	GLint success;
	glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetProgramInfoLog(shaderId, sizeof(infoLog), nullptr, infoLog);
		std::string msg = std::string("Shader program linking:\n") + infoLog;
		throw gkom::exception(msg);
	}

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
}

void Shader::setBool(const std::string &name, bool value) const {
	glUniform1i(glGetUniformLocation(getID(), name.c_str()), (int) value);
}

void Shader::setInt(const std::string &name, int value) const {
	glUniform1i(glGetUniformLocation(getID(), name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
	glUniform1f(glGetUniformLocation(getID(), name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
	glUniform2fv(glGetUniformLocation(getID(), name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y) const {
	glUniform2f(glGetUniformLocation(getID(), name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
	glUniform3fv(glGetUniformLocation(getID(), name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(getID(), name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
	glUniform4fv(glGetUniformLocation(getID(), name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const {
	glUniform4f(glGetUniformLocation(getID(), name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
	glUniformMatrix2fv(glGetUniformLocation(getID(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
	glUniformMatrix3fv(glGetUniformLocation(getID(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
	glUniformMatrix4fv(glGetUniformLocation(getID(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setLight(const std::string &name, const Light &light) const {
	setVec3(name + ".position", light.position);
	setVec3(name + ".ambient", light.ambient);
	setVec3(name + ".specular", light.specular);
	setVec3(name + ".diffuse", light.diffuse);
}


