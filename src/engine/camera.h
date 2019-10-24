#pragma once

#include "src/_classdef.h"
#include "src/opengl.h"

namespace engine {

	class Camera {
	public:
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;

		glm::mat4 getMatrix() const {
			return glm::lookAt(position, position + front, up);
		}
	};
}

