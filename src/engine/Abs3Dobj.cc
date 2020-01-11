/**
 * @file Abs3Dobj.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Abs3Dobj.h"
#include "Point.hpp"

using namespace engine;

Abs3DObj::Abs3DObj(Sub3DObjPtr parent) : Sub3DObj(parent) {

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	Point3DeX::BindGlVAP();
}

Abs3DObj::~Abs3DObj() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Abs3DObj::insertToGPU() {
	updateBuffers();

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	vertices_length_in_buffer = sizeof(Point3DeX) * vertices_buffer.size();
	glBufferData(GL_ARRAY_BUFFER, vertices_length_in_buffer, &vertices_buffer[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	indices_length_in_buffer = sizeof(EboTriangle) * indices_buffer.size();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_length_in_buffer, &indices_buffer[0], GL_STATIC_DRAW);

	setNeedRefreshBuffers(false);
}

void Abs3DObj::drawTriangles() {

	if (isNeedRefreshBuffers())
		insertToGPU();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 3 * indices_length_in_buffer, GL_UNSIGNED_INT, nullptr);
}


void recursiveUpdateBuffers(Sub3DObj *obj) {

	if (obj->isNeedRefreshBuffers())
		obj->updateBuffers();

	for (auto &child : obj->getChildren()) {
		if (child->isNeedRefreshBuffers())
			child->updateBuffers();
		recursiveUpdateBuffers(child);
	}
}

void Abs3DObj::updateBuffers() {
	vertices_buffer.clear();
	indices_buffer.clear();

	for (auto &child : getChildren()) {
		recursiveUpdateBuffers(child);
		child->insertToBuffers(vertices_buffer, indices_buffer);
	}

	setNeedRefreshBuffers(false);
}
