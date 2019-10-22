#pragma once

#include <GL/glew.h>
#include <vector>
#include "src/_classdef.h"
#include "scene.h"

namespace engine {
	class abs3DObj {
	protected:

		GLuint VAO, VBO, EBO;

		std::vector<engine::Point3DeX> vertices;
		std::vector<engine::SimpleTriangle> indices;

		void draw();
		void draw(uint32_t from, uint32_t count);
	public:
		glm::mat4 modelMatrix;

		abs3DObj();
		~abs3DObj();

		virtual void render(Scene *scene) = 0;

		void insertObjToBuffers();
	};
}

