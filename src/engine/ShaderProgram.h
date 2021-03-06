/**
 * @file ShaderProgram.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <string>

#include "src/_classdef.h"
#include "Light.h"

namespace engine {

	/**
	 * @brief Reprezentacja programu w karcie graficznej
	 */
	class ShaderProgram {
		GLuint shader_id;
	public:
		ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath);
		~ShaderProgram();

		virtual void bind();
		virtual void unbind();

		// returns program ID
		[[nodiscard]] inline GLuint getID() const {
			return shader_id;
		}

		void setBool(const std::string &name, bool value);
		void setInt(const std::string &name, int value);
		void setFloat(const std::string &name, float value);
		void setVec2(const std::string &name, const glm::vec2 &value);
		void setVec2(const std::string &name, float x, float y);
		void setVec3(const std::string &name, const glm::vec3 &value);
		void setVec3(const std::string &name, float x, float y, float z);
		void setVec4(const std::string &name, const glm::vec4 &value);
		void setVec4(const std::string &name, float x, float y, float z, float w);
		void setMat2(const std::string &name, const glm::mat2 &mat);
		void setMat3(const std::string &name, const glm::mat3 &mat);
		void setMat4(const std::string &name, const glm::mat4 &mat);

		void setUniformNameToId(const std::string& name, int id);
	};
}
