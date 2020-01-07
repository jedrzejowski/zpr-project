/**
 * @file InterfaceShader.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/engine/Engine.h"

namespace gui {

	class InterfaceShader : engine::Shader {
	private:

		const engine::Texture *guiTexture = nullptr;
		const engine::Texture *fontTexture = nullptr;
		const engine::Texture *blockTexture = nullptr;

	public:
		explicit InterfaceShader();

		void bind() override;
		void unbind() override;

		void setModel(const glm::mat4 &model);
	};
}

