/**
 * @file glmEx.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <src/engine/Camera.h>
#include "OpenGL.h"

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
		Triangle first_triangle{}, second_triangle{};
		glm::vec3 first_point{}, second_point{}, third_point{}, fourth_point{};

		Square() = default;

		Square(const Triangle &firstTriangle,
			   const Triangle &secondTriangle) :
				first_triangle(firstTriangle),
				second_triangle(secondTriangle),
				first_point(firstTriangle.first),
				second_point(firstTriangle.third),
				third_point(firstTriangle.second),
				fourth_point(firstTriangle.second) {}

		Square(const vec3 &first_point,
			   const vec3 &second_point,
			   const vec3 &third_point,
			   const vec3 &fourth_point) :
				first_point(first_point),
				second_point(second_point),
				third_point(third_point),
				fourth_point(fourth_point),
				first_triangle(first_point, third_point, second_point),
				second_triangle(first_point, fourth_point, third_point) {}

		template<typename T>
		bool intersectCamera(
				engine::Camera &camera,
				glm::vec2 &baryPosition,
				T &distance) {
			return glm::intersectRayTriangle(
					camera.position,
					camera.front,
					first_point,
					third_point,
					second_point,
					baryPosition,
					distance
			) || glm::intersectRayTriangle(
					camera.position,
					camera.front,
					first_point,
					fourth_point,
					third_point,
					baryPosition,
					distance
			);
		}
	};
}