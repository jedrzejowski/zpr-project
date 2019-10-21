//
// Created by adam on 07.04.18.
//

#include <math.h>
#include <glm/gtx/normal.hpp>

#include "Point3D.h"

using namespace engine;

uint32_t Point3D::SIZE = sizeof(Point3D);
uint32_t Normal::SIZE = sizeof(Normal);
uint32_t Color::SIZE = sizeof(Color);
uint32_t TexCoord::SIZE = sizeof(TexCoord);
uint32_t Point3DeX::SIZE = sizeof(Point3DeX);
uint32_t SimpleTriangle::SIZE = sizeof(SimpleTriangle);

SimpleTriangle SimpleTriangle::operator+(const int &n) {
	return SimpleTriangle(this->first + n, this->second + n, this->third + n);
}

SimpleTriangle &SimpleTriangle::operator+=(const int &n) {
	this->first += n;
	this->second += n;
	this->third += n;
	return *this;
}

uint32_t Point3D::OFFSET = 0;
uint32_t Normal::OFFSET = Point3D::OFFSET + Point3D::SIZE;
uint32_t Color::OFFSET = Normal::OFFSET + Normal::SIZE;
uint32_t TexCoord::OFFSET = Color::OFFSET + Color::SIZE;

void Point3DeX::BindGlVAP() {

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Point3DeX::SIZE, (void *) Point3D::OFFSET);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, Point3DeX::SIZE, (void *) Normal::OFFSET);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, Point3DeX::SIZE, (void *) Color::OFFSET);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, Point3DeX::SIZE, (void *) TexCoord::OFFSET);
	glEnableVertexAttribArray(3);
}

void Point3DeX::CalcNormals(Point3DeX *points, size_t pSize, SimpleTriangle *triangles, size_t tSize) {
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