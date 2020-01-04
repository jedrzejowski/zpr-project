#pragma once

#include <cinttypes>
#include "src/opengl.h"

typedef int64_t CoordDim;

inline std::string coordDim2string(CoordDim dim) {
	return std::string(dim < 0 ? "m" : "p") + std::to_string(std::abs(dim));
}

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

	json toJSON() const {
		json j;
		j["x"] = x;
		j["y"] = y;
		j["z"] = z;
		return j;
	}

	std::string toStringId() const {
		return coordDim2string(x) + "_" + coordDim2string(y) + "_" + coordDim2string(z);
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

	json toJSON() const {
		json j;
		j["x"] = x;
		j["y"] = y;
		return j;
	}

	std::string toStringId() const {
		return coordDim2string(x) + "_" + coordDim2string(y);
	}
};

inline std::ostream &operator<<(std::ostream &out, const Coord3D &coord) {
	return out << "Coord3D(" << coord.x << ", " << coord.y << ", " << coord.z << ")";
}

inline std::ostream &operator<<(std::ostream &out, const Coord2D &coord) {
	return out << "Coord2D(" << coord.x << ", " << coord.y << ")";
}

inline bool operator==(const Coord2D &left, const Coord2D &right) {
	return left.x == right.x && left.y == right.y;
}

inline bool operator==(const Coord3D &left, const Coord3D &right) {
	return left.x == right.x && left.y == right.y && left.z == right.z;
}