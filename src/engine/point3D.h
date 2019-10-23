#pragma once

#include "src/_classdef.h"
#include "opengl.h"

namespace engine {

	struct Point3D {
		static uint32_t SIZE;
		static uint32_t OFFSET;

		static float DistanceBetween(const Point3D &point1, const Point3D &point2);

		GLfloat x = 0.0f;
		GLfloat y = 0.0f;
		GLfloat z = 0.0f;

		Point3D() : Point3D(0.0f, 0.0f) {}

		Point3D(GLfloat x, GLfloat y) : Point3D(x, y, 0.0f) {}

		Point3D(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}
	};

	struct Normal {
		static uint32_t SIZE;
		static uint32_t OFFSET;

		GLfloat x = 0.0f;
		GLfloat y = 0.0f;
		GLfloat z = 0.0f;

		Normal() : Normal(0.0f, 0.0f) {}

		Normal(GLfloat x, GLfloat y) : Normal(x, y, 0.0f) {}

		Normal(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}
	};

	struct TexCoord {
		static uint32_t SIZE;
		static uint32_t OFFSET;

		GLfloat X = 0.0f;
		GLfloat Y = 0.0f;

		TexCoord() : TexCoord(0.0f, 0.0f) {}

		TexCoord(GLfloat X, GLfloat Y) : X(X), Y(Y) {}
	};

	struct SimpleTriangle {
		uint32_t first;
		uint32_t second;
		uint32_t third;

		static uint32_t SIZE;

		SimpleTriangle() : first(0), second(0), third(0) {}

		SimpleTriangle(const uint32_t first, const uint32_t second, const uint32_t third) : first(first),
																							second(second),
																							third(third) {}

		SimpleTriangle operator+(const int &n);

		SimpleTriangle &operator+=(const int &n);
	};

	struct Point3DeX {
		static uint32_t SIZE;

		static void BindGlVAP();

		static void CalcNormals(Point3DeX *points, size_t pSize, SimpleTriangle *triangles, size_t tSize);

		Point3D point;
		Normal normal;
		TexCoord texture;

		Point3DeX() {}

		Point3DeX(Point3D p) : point(p) {}

		Point3DeX(Point3D p, TexCoord t) : point(p), texture(t) {}

		Point3DeX(GLfloat X, GLfloat Y, GLfloat Z) : point(X, Y, Z) {}

		Point3DeX(GLfloat X, GLfloat Y, GLfloat Z, TexCoord t) : point(X, Y, Z), texture(t) {}
	};
}
