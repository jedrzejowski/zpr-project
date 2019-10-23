#pragma once

#include "src/_classdef.h"
#include "opengl.h"

namespace engine {

	class Light {
	public:

		glm::vec3 position;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
}