//
// Created by adam on 07.04.18.
//

#include "abs3DObj.h"
#include "point3D.h"

using namespace engine;

abs3DObj::abs3DObj() {

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

abs3DObj::~abs3DObj() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void abs3DObj::insertObjToBuffers() {

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Point3DeX::SIZE * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	Point3DeX::BindGlVAP();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, SimpleTriangle::SIZE * indices.size(), &indices[0], GL_STATIC_DRAW);

}

void abs3DObj::draw() {

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 3 * indices.size(), GL_UNSIGNED_INT, nullptr);

}

void abs3DObj::draw(uint32_t from, uint32_t count) {

	glBindVertexArray(VAO);
	glDrawRangeElements(GL_TRIANGLES, 3 * from, 3 * (from + count) - 1, 3 * count, GL_UNSIGNED_INT, nullptr);

}
