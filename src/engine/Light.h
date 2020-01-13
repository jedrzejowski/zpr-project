/**
 * @file Light.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/OpenGL.h"

namespace engine {

	/**
	 * @brief Światło, nie używane
	 */
	class Light {
	public:

		glm::vec3 position;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
}
