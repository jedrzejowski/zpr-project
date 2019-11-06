#pragma once

#include "src/_classdef.h"
#include "src/opengl.h"

namespace engine {


	struct Point3D {

		static float DistanceBetween(const Point3D &point1, const Point3D &point2);

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		Point3D() : Point3D(0.0f, 0.0f) {}

		Point3D(float x, float y) : Point3D(x, y, 0.0f) {}

		Point3D(float x, float y, float z) : x(x), y(y), z(z) {}

		Point3D(glm::vec3 vec) : x(vec.x), y(vec.y), z(vec.z) {}

		Point3D(glm::vec4 vec) : x(vec.x / vec[3]), y(vec.y / vec[3]), z(vec.z / vec[3]) {}
	};

	struct Normal {

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		Normal() : Normal(0.0f, 0.0f) {}

		Normal(float x, float y) : Normal(x, y, 0.0f) {}

		Normal(float x, float y, float z) : x(x), y(y), z(z) {}
	};

	struct TexCoord {

		float x = 0.0f;
		float y = 0.0f;
		uint32_t no = 1;

		TexCoord() : TexCoord(0.0f, 0.0f) {}

		TexCoord(float x, float y) : x(x), y(y) {}
	};

	struct SimpleTriangle {
		uint32_t first;
		uint32_t second;
		uint32_t third;

		SimpleTriangle() : first(0), second(0), third(0) {}

		SimpleTriangle(const uint32_t first, const uint32_t second, const uint32_t third) :
				first(first), second(second), third(third) {}

		SimpleTriangle operator+(const int &n);

		SimpleTriangle &operator+=(const int &n);
	};

	inline std::ostream &operator<<(std::ostream &out, const SimpleTriangle &tringle) {
		return out << "SimpleTriangle(" << tringle.first << ", " << tringle.second << ", " << tringle.third << ")";
	}

	struct Color {

		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;
		float a = 1.0f;

		Color() : Color(0.0f, 0.0f, 0.0f) {}

		Color(float gray) : r(gray), g(gray), b(gray) {}

		Color(float r, float g, float b) : r(r), g(g), b(b) {}

		Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
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

		Point3DeX(float x, float y, float z) : point(x, y, z) {}

		Point3DeX(float x, float y, float z, TexCoord t) : point(x, y, z), texture(t) {}
	};
}
