//
// Created by adam on 07.04.18.
//

#include "abs3DObj.h"
#include "point.h"

using namespace engine;

Abs3DObj::Abs3DObj() {

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

Abs3DObj::~Abs3DObj() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Abs3DObj::insertObjToBuffers() {

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Point3DeX) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	Point3DeX::BindGlVAP();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SimpleTriangle) * indices.size(), &indices[0], GL_STATIC_DRAW);

}

void Abs3DObj::draw() {

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 3 * indices.size(), GL_UNSIGNED_INT, nullptr);

}

void Abs3DObj::draw(uint32_t from, uint32_t count) {

	glBindVertexArray(VAO);
	glDrawRangeElements(GL_TRIANGLES, 3 * from, 3 * (from + count) - 1, 3 * count, GL_UNSIGNED_INT, nullptr);

}
