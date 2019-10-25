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

void Abs3DObj::insertToBuffers() {
	logger.log("insertToBuffers");
	updateBuffers();
	needRefreshBuffers = false;

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	verticesLengthInBuffer = sizeof(Point3DeX) * vertices.size();
	glBufferData(GL_ARRAY_BUFFER, verticesLengthInBuffer, &vertices[0], GL_STATIC_DRAW);

	Point3DeX::BindGlVAP();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	indicesLengthInBuffer = sizeof(SimpleTriangle) * indices.size();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLengthInBuffer, &indices[0], GL_STATIC_DRAW);
}

void Abs3DObj::draw() {

	if (needRefreshBuffers)
		insertToBuffers();


	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 3 * indicesLengthInBuffer, GL_UNSIGNED_INT, nullptr);
}

bool Abs3DObj::isNeedRefreshBuffers() const {
	return needRefreshBuffers;
}

void Abs3DObj::setNeedRefreshBuffers(bool needRefreshBuffers) {
	Abs3DObj::needRefreshBuffers = needRefreshBuffers;
}
