#pragma once

#include "opengl.h"

namespace glm {

	struct Triangle {
	public:
		glm::vec3 first{}, second{}, third{};

		Triangle() = default;

		Triangle(const vec3 &first,
				 const vec3 &second,
				 const vec3 &third) :
				first(first),
				second(second),
				third(third) {}
	};

	class Square {
	public:
		Triangle first{}, second{};

		Square() = default;

		Square(const Triangle &first,
			   const Triangle &second) :
				first(first),
				second(second) {}

		template<typename T>
		bool intersectRay(
				const glm::vec3 &orig,
				const glm::vec3 &dir,
				glm::vec2 &baryPosition,
				T &distance) {
			return glm::intersectRayTriangle(
					orig,
					dir,
					first.first,
					first.second,
					first.third,
					baryPosition,
					distance
			) || glm::intersectRayTriangle(
					orig,
					dir,
					second.first,
					second.second,
					second.third,
					baryPosition,
					distance
			);
		}
	};
}