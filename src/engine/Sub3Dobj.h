/**
 * @file Sub3Dobj.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <list>

#include "src/_classdef.h"
#include "src/lib/Object.hpp"
#include "Point.hpp"

namespace engine {
	class Sub3DObj {
	private:
		std::list<Sub3DObj *> children;
		Sub3DObjWPtr parent_wptr;
		bool is_need_refresh_buffers = true;

	protected:

		std::vector<engine::Point3DeX> vertices_buffer;
		std::vector<engine::EboTriangle> indices_buffer;

	public:
		explicit Sub3DObj(Sub3DObjPtr parent);
		~Sub3DObj();

		[[nodiscard]] Sub3DObjWPtr getParent() const;
		void setParent(Sub3DObjPtr parent);

		[[nodiscard]] const std::list<Sub3DObj *> &getChildren() const;

		void insertToBuffers(
				std::vector<engine::Point3DeX> &vertices,
				std::vector<engine::EboTriangle> &indices);

		virtual void updateBuffers() = 0;

		[[nodiscard]] virtual bool isNeedRefreshBuffers() const;
		virtual void setNeedRefreshBuffers(bool needRefreshBuffers);
	};
}
