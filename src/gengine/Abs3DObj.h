#pragma once

#include <GL/glew.h>
#include "Scene.h"

namespace gengine {
	class Abs3DObj {
	protected:

		GLuint VAO, VBO, EBO;
		Scene* anim;

		struct Point3DeX* vertices;
		struct SimpleTriangle* indices;
		uint verticesNum;
		uint indicesNum;

		void draw();
		void draw(uint from, uint count);
	public:
		glm::mat4 modelMatrix;

		Abs3DObj(Scene* anim);

		~Abs3DObj();
		virtual void render(Window *window) = 0;

		void insertObjToBuffers();

	};
}

