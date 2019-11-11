#pragma once

#include <vector>
#include "src/_classdef.h"
#include "scene.h"
#include "sub3Dobj.h"

namespace engine {
	class Abs3DObj : public Sub3DObj {
	private:
		GLuint VAO, VBO, EBO;
		bool needRefreshBuffers = true;
		std::size_t verticesLengthInBuffer = 0,
				indicesLengthInBuffer = 0;
	protected:

		void draw();
		void insertToGPU();

	public:

		Abs3DObj();
		~Abs3DObj();

		void updateBuffers() override;
		virtual void render(const Scene *scene) = 0;

		bool isNeedRefreshBuffers() const;
		void setNeedRefreshBuffers(bool needRefreshBuffers);

	};
}

