//
// Created by adam on 05.11.2019.
//

#include "sub3Dobj.h"
#include "point.h"

engine::Sub3DObj::Sub3DObj(engine::Sub3DObj *parent) {
	set3DParent(parent);
}

engine::Sub3DObj *engine::Sub3DObj::get3DParent() const {
	return parent3D;
}

void engine::Sub3DObj::set3DParent(engine::Sub3DObj *newParent) {
	if (this->parent3D != nullptr)
		this->parent3D->childrens.remove(this);
	this->parent3D = newParent;
	if (this->parent3D != nullptr)
		this->parent3D->childrens.push_back(this);
}

const std::list<engine::Sub3DObj *> &engine::Sub3DObj::getChildrens() const {
	return childrens;
}

void engine::Sub3DObj::insertToBuffers(std::vector<engine::Point3DeX> &vertices,
									   std::vector<engine::SimpleTriangle> &indices) {

	auto vOffset = vertices.size();
	vertices.insert(vertices.end(), verticesBuf.begin(), verticesBuf.end());

	auto iOffset = indices.size();
	indices.insert(indices.end(), indicesBuf.begin(), indicesBuf.end());

	for (int i = iOffset; i < indices.size(); i++)
		indices[i] += vOffset;

	setNeedRefreshBuffers(false);

	for (auto &child : getChildrens())
		child->insertToBuffers(vertices, indices);
}

bool engine::Sub3DObj::isNeedRefreshBuffers() const {
	return needRefreshBuffers;
}

void engine::Sub3DObj::setNeedRefreshBuffers(bool needRefreshBuffers) {
	Sub3DObj::needRefreshBuffers = needRefreshBuffers;
}