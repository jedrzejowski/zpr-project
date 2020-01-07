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
		Triangle firstTriangle{}, secondTriangle{};
		glm::vec3 firstPoint{}, secondPoint{}, thirdPoint{}, fourthPoint{};

		Square() = default;

		Square(const Triangle &firstTriangle,
			   const Triangle &secondTriangle) :
				firstTriangle(firstTriangle),
				secondTriangle(secondTriangle),
				firstPoint(firstTriangle.first),
				secondPoint(firstTriangle.third),
				thirdPoint(firstTriangle.second),
				fourthPoint(firstTriangle.second) {}

		Square(const vec3 &firstPoint,
			   const vec3 &secondPoint,
			   const vec3 &thirdPoint,
			   const vec3 &fourthPoint) :
				firstPoint(firstPoint),
				secondPoint(secondPoint),
				thirdPoint(thirdPoint),
				fourthPoint(fourthPoint),
				firstTriangle(firstPoint, thirdPoint, secondPoint),
				secondTriangle(firstPoint, fourthPoint, thirdPoint) {}

		template<typename T>
		bool intersectCamera(
				engine::Camera &camera,
				glm::vec2 &baryPosition,
				T &distance) {
			return glm::intersectRayTriangle(
					camera.position,
					camera.front,
					firstPoint,
					thirdPoint,
					secondPoint,
					baryPosition,
					distance
			) || glm::intersectRayTriangle(
					camera.position,
					camera.front,
					firstPoint,
					fourthPoint,
					thirdPoint,
					baryPosition,
					distance
			);
		}
	};
}