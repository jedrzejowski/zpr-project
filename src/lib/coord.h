#pragma once

#include <cinttypes>
#include "src/opengl.h"

typedef int64_t CoordDim;

struct Coord3D {
	CoordDim x, y, z;

	Coord3D() : x(0), y(0), z(0) {}
	Coord3D(CoordDim x, CoordDim y, CoordDim z) : x(x), y(y), z(z) {}
	Coord3D(const glm::vec3 &vec) : x(vec.x), y(vec.y), z(vec.z) {}

	bool operator<(const Coord3D &sec) const {
		if (x < sec.x) return true;
		if (x > sec.x) return false;

		if (y < sec.y) return true;
		if (y > sec.y) return false;

		return z < sec.z;
	}
};

struct Coord2D {
	CoordDim x, y;

	Coord2D() : x(0), y(0) {}
	Coord2D(CoordDim x, CoordDim y) : x(x), y(y) {}
	Coord2D(const glm::vec2 &vec) : x(vec.x), y(vec.y) {}

	bool operator<(const Coord2D &sec) const {
		if (x < sec.x) return true;
		if (x > sec.x) return false;
		return y < sec.y;
	}
};

inline std::ostream &operator<<(std::ostream &out, const Coord3D &coord) {
	return out << "Coord3D(" << coord.x << ", " << coord.y << ", " << coord.z << ")";
}

inline std::ostream &operator<<(std::ostream &out, const Coord2D &coord) {
	return out << "Coord2D(" << coord.x << ", " << coord.y << ")";
}