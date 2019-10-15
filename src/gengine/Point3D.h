//
// Created by adam on 07.04.18.
//

#ifndef GKOM_ANIMATION_POINT_H
#define GKOM_ANIMATION_POINT_H

#include <GL/glew.h>
#include <glm/vec3.hpp>

namespace gengine {

	struct Point3DeX;

	struct Point3D {
		static uint SIZE;
		static uint OFFSET;

		static float DistanceBetween(const Point3D &point1, const Point3D &point2);

		GLfloat x = 0.0f;
		GLfloat y = 0.0f;
		GLfloat z = 0.0f;

		Point3D() : Point3D(0.0f, 0.0f) {}

		Point3D(GLfloat x, GLfloat y) : Point3D(x, y, 0.0f) {}

		Point3D(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}
	};

	struct Normal {
		static uint SIZE;
		static uint OFFSET;

		GLfloat x = 0.0f;
		GLfloat y = 0.0f;
		GLfloat z = 0.0f;

		Normal() : Normal(0.0f, 0.0f) {}

		Normal(GLfloat x, GLfloat y) : Normal(x, y, 0.0f) {}

		Normal(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}
	};

	struct Color {
		static uint SIZE;
		static uint OFFSET;

		GLfloat R = 0.0f;
		GLfloat G = 0.0f;
		GLfloat B = 0.0f;

		Color() : Color(0.0f, 0.0f, 0.0f) {}

		Color(GLfloat gray) : R(gray), G(gray), B(gray) {}

		Color(GLfloat R, GLfloat G, GLfloat B) : R(R), G(G), B(B) {}
	};

	struct TexCoord {
		static uint SIZE;
		static uint OFFSET;

		GLfloat X = 0.0f;
		GLfloat Y = 0.0f;

		TexCoord() : TexCoord(0.0f, 0.0f) {}

		TexCoord(GLfloat X, GLfloat Y) : X(X), Y(Y) {}
	};

	struct SimpleTriangle {
		uint first;
		uint second;
		uint third;

		static uint SIZE;

		SimpleTriangle() : first(0), second(0), third(0) {}

		SimpleTriangle(const uint first, const uint second, const uint third) : first(first), second(second),
																				third(third) {}

		SimpleTriangle operator+(const int &n);

		SimpleTriangle &operator+=(const int &n);
	};

	struct Point3DeX {
		static uint SIZE;

		static void BindGlVAP();

		static void CalcNormals(Point3DeX *points, size_t pSize, SimpleTriangle *triangles, size_t tSize);

		Point3D point;
		Normal normal;
		Color color;
		TexCoord texture;

		Point3DeX() {}

		Point3DeX(Point3D p) : point(p) {}

		Point3DeX(Point3D p, Color c) : point(p), color(c) {}

		Point3DeX(Point3D p, TexCoord t) : point(p), texture(t) {}

		Point3DeX(Point3D p, Color c, TexCoord t) : point(p), color(c), texture(t) {}

		Point3DeX(GLfloat X, GLfloat Y, GLfloat Z) : point(X, Y, Z), color() {}

		Point3DeX(GLfloat X, GLfloat Y, GLfloat Z, Color c) : point(X, Y, Z), color(c) {}

		Point3DeX(GLfloat X, GLfloat Y, GLfloat Z, TexCoord t) : point(X, Y, Z), texture(t) {}

		Point3DeX(GLfloat X, GLfloat Y, GLfloat Z, Color c, TexCoord t) : point(X, Y, Z), color(c), texture(t) {}

		Point3DeX(GLfloat X, GLfloat Y, GLfloat Z, GLfloat R, GLfloat G, GLfloat B) : point(X, Y, Z),
																					  color(R, G, B) {}
	};
}
#endif //GKOM_ANIMATION_POINT_H
