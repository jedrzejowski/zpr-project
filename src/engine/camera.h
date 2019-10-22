#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "src/_classdef.h"

namespace engine {

	class camera {
	public:
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;

		glm::mat4 getMatrix() const {
			return glm::lookAt(position, position + front, up);
		}
	};
}

