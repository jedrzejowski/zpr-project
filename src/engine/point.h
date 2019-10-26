#pragma once

#include "src/_classdef.h"
#include "src/opengl.h"

namespace engine {


	struct Point3D {

		static float DistanceBetween(const Point3D &point1, const Point3D &point2);

		GLfloat x = 0.0f;
		GLfloat y = 0.0f;
		GLfloat z = 0.0f;

		Point3D() : Point3D(0.0f, 0.0f) {}

		Point3D(GLfloat x, GLfloat y) : Point3D(x, y, 0.0f) {}

		Point3D(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}

		Point3D(glm::vec3 vec) : x(vec.x), y(vec.y), z(vec.z) {}

		Point3D(glm::vec4 vec) : x(vec.x / vec[3]), y(vec.y / vec[3]), z(vec.z / vec[3]) {}
	};

	struct Normal {

		GLfloat x = 0.0f;
		GLfloat y = 0.0f;
		GLfloat z = 0.0f;

		Normal() : Normal(0.0f, 0.0f) {}

		Normal(GLfloat x, GLfloat y) : Normal(x, y, 0.0f) {}

		Normal(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}
	};

	struct TexCoord {

		GLfloat x = 0.0f;
		GLfloat y = 0.0f;

		TexCoord() : TexCoord(0.0f, 0.0f) {}

		TexCoord(GLfloat x, GLfloat y) : x(x), y(y) {}
	};

	struct SimpleTriangle {
		uint32_t first;
		uint32_t second;
		uint32_t third;

		SimpleTriangle() : first(0), second(0), third(0) {}

		SimpleTriangle(const uint32_t first, const uint32_t second, const uint32_t third) : first(first),
																							second(second),
																							third(third) {}

		SimpleTriangle operator+(const int &n);

		SimpleTriangle &operator+=(const int &n);
	};

	struct Point3DeX {

		static void BindGlVAP();

		static void CalcNormals(Point3DeX *points, size_t pSize, SimpleTriangle *triangles, size_t tSize);

		Point3D point;
		Normal normal;
		TexCoord texture;

		Point3DeX() = default;

		Point3DeX(Point3D p) : point(p) {}

		Point3DeX(Point3D p, TexCoord t) : point(p), texture(t) {}

		Point3DeX(glm::vec3 p, TexCoord t) : point(p), texture(t) {}

		Point3DeX(glm::vec4 p, TexCoord t) : point(p), texture(t) {}

		Point3DeX(GLfloat x, GLfloat y, GLfloat z) : point(x, y, z) {}

		Point3DeX(GLfloat x, GLfloat y, GLfloat z, TexCoord t) : point(x, y, z), texture(t) {}
	};
}
