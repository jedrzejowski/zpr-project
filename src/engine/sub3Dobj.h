#pragma once

#include <list>

#include "src/_classdef.h"
#include "src/lib/object.h"
#include "point.h"

namespace engine {
	class Sub3DObj {
	private:
		std::list<Sub3DObj *> childrens;
		Sub3DObj *parent3D = nullptr;
		bool needRefreshBuffers = true;

	protected:

		std::vector<engine::Point3DeX> verticesBuf;
		std::vector<engine::SimpleTriangle> indicesBuf;

	public:
		explicit Sub3DObj(Sub3DObj *parent = nullptr);

		Sub3DObj *get3DParent() const;
		void set3DParent(Sub3DObj *newParent);

		const std::list<Sub3DObj *> &getChildrens() const;

		void insertToBuffers(
				std::vector<engine::Point3DeX> &vertices,
				std::vector<engine::SimpleTriangle> &indices);

		virtual void updateBuffers() = 0;

		bool isNeedRefreshBuffers() const;
		void setNeedRefreshBuffers(bool needRefreshBuffers);
	};
}
