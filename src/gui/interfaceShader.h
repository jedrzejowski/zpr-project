#pragma once

#include "src/engine/Engine.h"

namespace gui {

	class InterfaceShader {
	private:

		engine::ShaderProgram *shader = nullptr;
		const engine::Texture *guiTexture = nullptr;
		const engine::Texture *fontTexture = nullptr;

	public:
		explicit InterfaceShader();

		void bind();
		void unbind();

		void setModel(const glm::mat4& model);
	};
}

