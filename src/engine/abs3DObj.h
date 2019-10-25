#pragma once

#include <vector>
#include "src/_classdef.h"
#include "scene.h"

namespace engine {
	class Abs3DObj {
	private:
		GLuint VAO, VBO, EBO;
		bool needRefreshBuffers = true;
		std::size_t verticesLengthInBuffer = 0,
				indicesLengthInBuffer = 0;
	protected:

		std::vector<engine::Point3DeX> vertices;
		std::vector<engine::SimpleTriangle> indices;

		void draw();
		virtual void updateBuffers() {};
		void insertToBuffers();

	public:

		Abs3DObj();
		~Abs3DObj();

		virtual void render(const Scene *scene) = 0;

		bool isNeedRefreshBuffers() const;
		void setNeedRefreshBuffers(bool needRefreshBuffers);
	};
}

