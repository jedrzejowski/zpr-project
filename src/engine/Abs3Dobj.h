/**
 * @file Abs3Dobj.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <vector>
#include "src/_classdef.h"
#include "Scene.h"
#include "Sub3DObj.h"

namespace engine {
	class Abs3DObj : public Sub3DObj {
	private:
		GLuint VAO, VBO, EBO;
		std::size_t vertices_length_in_buffer = 0,
				indices_length_in_buffer = 0;
	protected:

		void drawTriangles();
		void insertToGPU();

	public:

		explicit Abs3DObj(Sub3DObjPtr parent = nullptr);
		~Abs3DObj();

		void updateBuffers() override;
		virtual void render(const ScenePtr& scene) = 0;

	};
}

