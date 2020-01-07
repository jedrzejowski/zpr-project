/**
 * @file Point.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include <math.h>

#include "Point.hpp"

using namespace engine;

void Point3DeX::BindGlVAP() {

	uint64_t offset = 0;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point3DeX), (void *) offset);
	glEnableVertexAttribArray(0);
	offset += sizeof(Point3D);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Point3DeX), (void *) offset);
	glEnableVertexAttribArray(1);
	offset += sizeof(Normal);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Point3DeX), (void *) offset);
	glEnableVertexAttribArray(2);
	offset += sizeof(float) * 2;

	glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(Point3DeX), (void *) offset);
	glEnableVertexAttribArray(3);
	offset += sizeof(uint32_t);
}

void Point3DeX::CalcNormals(Point3DeX *points, size_t pSize, EboTriangle *triangles, size_t tSize) {
	glm::vec3 temp1, temp2, temp3, temp4;

	for (uint32_t i = 0; i < tSize; i++) {
		temp1 = glm::vec3(points[triangles[i].first].point.x,
						  points[triangles[i].first].point.y,
						  points[triangles[i].first].point.z);

		temp2 = glm::vec3(points[triangles[i].second].point.x,
						  points[triangles[i].second].point.y,
						  points[triangles[i].second].point.z);

		temp3 = glm::vec3(points[triangles[i].third].point.x,
						  points[triangles[i].third].point.y,
						  points[triangles[i].third].point.z);

		temp4 = glm::triangleNormal(temp2, temp1, temp3);

		points[triangles[i].first].normal.x = temp4.x;
		points[triangles[i].first].normal.y = temp4.y;
		points[triangles[i].first].normal.z = temp4.z;

		points[triangles[i].second].normal.x = temp4.x;
		points[triangles[i].second].normal.y = temp4.y;
		points[triangles[i].second].normal.z = temp4.z;

		points[triangles[i].second].normal.x = temp4.x;
		points[triangles[i].second].normal.y = temp4.y;
		points[triangles[i].second].normal.z = temp4.z;
	}
}

float Point3D::DistanceBetween(const Point3D &point1, const Point3D &point2) {
	return (float) sqrt(
			pow(point1.x - point2.x, 2) +
			pow(point1.y - point2.y, 2) +
			pow(point1.z - point2.z, 2)
	);
}


EboTriangle EboTriangle::operator+(const int &n) {
	return EboTriangle(this->first + n, this->second + n, this->third + n);
}

EboTriangle &EboTriangle::operator+=(const int &n) {
	this->first += n;
	this->second += n;
	this->third += n;
	return *this;
}

EboTriangle EboTriangle::operator-(const int &n) {
	return EboTriangle(this->first - n, this->second - n, this->third - n);
}

EboTriangle &EboTriangle::operator-=(const int &n) {
	this->first -= n;
	this->second -= n;
	this->third -= n;
	return *this;
}
