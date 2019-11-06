//
// Created by adam on 07.04.18.
//

#include "abs3Dobj.h"
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

void Abs3DObj::insertToGPU() {
	updateBuffers();
	needRefreshBuffers = false;

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	verticesLengthInBuffer = sizeof(Point3DeX) * verticesBuf.size();
	glBufferData(GL_ARRAY_BUFFER, verticesLengthInBuffer, &verticesBuf[0], GL_STATIC_DRAW);

	Point3DeX::BindGlVAP();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	indicesLengthInBuffer = sizeof(SimpleTriangle) * indicesBuf.size();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLengthInBuffer, &indicesBuf[0], GL_STATIC_DRAW);

	setNeedRefreshBuffers(false);
}

void Abs3DObj::draw() {

	if (isNeedRefreshBuffers())
		insertToGPU();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 3 * indicesLengthInBuffer, GL_UNSIGNED_INT, nullptr);
}

bool Abs3DObj::isNeedRefreshBuffers() const {
	bool out = needRefreshBuffers;

	for (auto &child : getChildrens())
		out = out || child->isNeedRefreshBuffers();

	return out;
}

void Abs3DObj::setNeedRefreshBuffers(bool needRefreshBuffers) {
	Abs3DObj::needRefreshBuffers = needRefreshBuffers;
}

void Abs3DObj::updateBuffers() {
	verticesBuf.clear();
	indicesBuf.clear();

	for (auto &child : getChildrens()) {
		if (child->isNeedRefreshBuffers())
			child->updateBuffers();
		child->insertToBuffers(verticesBuf, indicesBuf);
	}
}
