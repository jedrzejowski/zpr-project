//
// Created by adam on 05.11.2019.
//

#include "Sub3Dobj.h"
#include "Point.hpp"

engine::Sub3DObj::Sub3DObj(engine::Sub3DObjPtr parent) {
	setParent(parent);
}

engine::Sub3DObjWPtr engine::Sub3DObj::getParent() const {
	return parentWPtr;
}

void engine::Sub3DObj::setParent(engine::Sub3DObjPtr newParent) {
	if (auto parentPtr = this->parentWPtr.lock())
		parentPtr->children.remove(this);

	this->parentWPtr = newParent;

	if (newParent != nullptr)
		if (auto parentPtr = this->parentWPtr.lock())
			parentPtr->children.push_back(this);
}

const std::list<engine::Sub3DObj *> &engine::Sub3DObj::getChildren() const {
	return children;
}

void engine::Sub3DObj::insertToBuffers(std::vector<engine::Point3DeX> &vertices,
									   std::vector<engine::EboTriangle> &indices) {

	auto vOffset = vertices.size();
	vertices.insert(vertices.end(), verticesBuf.begin(), verticesBuf.end());

	auto iOffset = indices.size();
	indices.insert(indices.end(), indicesBuf.begin(), indicesBuf.end());

	for (int i = iOffset; i < indices.size(); i++)
		indices[i] += vOffset;

	setNeedRefreshBuffers(false);

	for (auto &child : getChildren())
		child->insertToBuffers(vertices, indices);
}

bool engine::Sub3DObj::isNeedRefreshBuffers() const {
	return needRefreshBuffers;
}

void engine::Sub3DObj::setNeedRefreshBuffers(bool needRefreshBuffers) {
	Sub3DObj::needRefreshBuffers = needRefreshBuffers;
}

engine::Sub3DObj::~Sub3DObj() {
	if (auto parentPtr = this->parentWPtr.lock())
		parentPtr->children.remove(this);
}
