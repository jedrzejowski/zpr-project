/**
 * @file Sub3Dobj.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Sub3DObj.h"
#include "Point.hpp"

engine::Sub3DObj::Sub3DObj(engine::Sub3DObjPtr parent) {
	setParent(parent);
}

engine::Sub3DObjWPtr engine::Sub3DObj::getParent() const {
	return parent_wptr;
}

void engine::Sub3DObj::setParent(engine::Sub3DObjPtr newParent) {
	if (auto parentPtr = this->parent_wptr.lock())
		parentPtr->children.remove(this);

	this->parent_wptr = newParent;

	if (newParent != nullptr)
		if (auto parentPtr = this->parent_wptr.lock())
			parentPtr->children.push_back(this);
}

const std::list<engine::Sub3DObj *> &engine::Sub3DObj::getChildren() const {
	return children;
}

void engine::Sub3DObj::insertToBuffers(std::vector<engine::Point3DeX> &vertices,
									   std::vector<engine::EboTriangle> &indices) {

	auto vOffset = vertices.size();
	vertices.insert(vertices.end(), vertices_buffer.begin(), vertices_buffer.end());

	auto iOffset = indices.size();
	indices.insert(indices.end(), indices_buffer.begin(), indices_buffer.end());

	for (int i = iOffset; i < indices.size(); ++i)
		indices[i] += vOffset;

	setNeedRefreshBuffers(false);

	for (auto &child : getChildren())
		child->insertToBuffers(vertices, indices);
}

bool engine::Sub3DObj::isNeedRefreshBuffers() const {
	bool out = is_need_refresh_buffers;

	for (const auto &child : getChildren())
		out = out || child->isNeedRefreshBuffers();

	return out;
}

void engine::Sub3DObj::setNeedRefreshBuffers(bool need) {
	is_need_refresh_buffers = need;
}

engine::Sub3DObj::~Sub3DObj() {
	if (auto parentPtr = this->parent_wptr.lock())
		parentPtr->children.remove(this);
}

size_t engine::Sub3DObj::getChildCount() const {
	return children.size();
}
