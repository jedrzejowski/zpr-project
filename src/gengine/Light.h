#pragma once

#include <glm/vec3.hpp>

#include "_classdef.h"

namespace gengine {

	class Light {
	public:

		glm::vec3 position;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
}
