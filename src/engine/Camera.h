/**
 * @file Camera.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/OpenGL.h"

namespace engine {

	/**
	 * @brief Implementacja kamery
	 */
	class Camera {
	public:
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;

		/**
		 * @brief Tworzy macierz kamery
		 * @return
		 */
		[[nodiscard]] glm::mat4 getMatrix() const {
			return glm::lookAt(position, position + front, up);
		}
	};
}

