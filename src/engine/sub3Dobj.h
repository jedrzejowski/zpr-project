#pragma once

#include <list>

#include "src/_classdef.h"
#include "src/lib/object.h"
#include "point.h"

namespace engine {
	class Sub3DObj {
	private:
		std::list<Sub3DObj *> children;
		Sub3DObjWPtr parentWPtr;
		bool needRefreshBuffers = true;

	protected:

		std::vector<engine::Point3DeX> verticesBuf;
		std::vector<engine::SimpleTriangle> indicesBuf;

	public:
		explicit Sub3DObj(Sub3DObjPtr parent);
		~Sub3DObj();

		Sub3DObjWPtr getParent() const;
		void setParent(Sub3DObjPtr parent);

		const std::list<Sub3DObj *> &getChildren() const;

		void insertToBuffers(
				std::vector<engine::Point3DeX> &vertices,
				std::vector<engine::SimpleTriangle> &indices);

		virtual void updateBuffers() = 0;

		virtual bool isNeedRefreshBuffers() const;
		virtual void setNeedRefreshBuffers(bool needRefreshBuffers);
	};
}
