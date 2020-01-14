/**
 * @file InterfaceShader.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/engine/Engine.h"

namespace gui {

	/**
	 * @brief Shader interfejsu
	 */
	class InterfaceShader : engine::Shader {
	private:

		engine::TexturePtr gui_texture;
		engine::TexturePtr font_texture;
		engine::TexturePtr block_texture;

	public:
		explicit InterfaceShader();

		void bind() override;
		void unbind() override;

		void setModel(const glm::mat4 &model);
	};
}

