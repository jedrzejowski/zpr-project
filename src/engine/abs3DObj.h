#pragma once

#include <vector>
#include "src/_classdef.h"
#include "scene.h"

namespace engine {
	class Abs3DObj {
	private:
		GLuint VAO, VBO, EBO;
		bool needRefreshBuffers = true;
	protected:


		std::vector<engine::Point3DeX> vertices;
		std::vector<engine::SimpleTriangle> indices;

		void draw();
		void draw(uint32_t from, uint32_t count);

		void iChangedBuffers();
	public:

		Abs3DObj();
		~Abs3DObj();

		virtual void render(Scene *scene) = 0;

		void insertToBuffers();

		bool isNeedRefreshBuffers() const;
		void setNeedRefreshBuffers(bool needRefreshBuffers);
	};
}

