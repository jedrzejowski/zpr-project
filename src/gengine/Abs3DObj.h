#pragma once

#include <GL/glew.h>
#include "_classdef.h"
#include "Scene.h"

namespace gengine {
	class Abs3DObj {
	protected:

		GLuint VAO, VBO, EBO;

		struct Point3DeX* vertices;
		struct SimpleTriangle* indices;
		uint verticesNum;
		uint indicesNum;

		void draw();
		void draw(uint from, uint count);
	public:
		glm::mat4 modelMatrix;

		Abs3DObj();
		~Abs3DObj();

		virtual void render(Window *window) = 0;

		void insertObjToBuffers();

	};
}

