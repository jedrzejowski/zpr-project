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

		const engine::Texture *gui_texture = nullptr;
		const engine::Texture *font_texture = nullptr;
		const engine::Texture *block_texture = nullptr;

	public:
		explicit InterfaceShader();

		void bind() override;
		void unbind() override;

		void setModel(const glm::mat4 &model);
	};
}

