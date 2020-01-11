/**
 * @file Interface.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <list>
#include "src/_classdef.h"
#include "src/lib/Object.hpp"
#include "src/engine/Engine.h"
#include "InterfaceShader.h"

namespace gui {

	class Interface : public Object, public engine::Abs3DObj {
	private:
		engine::InputInterfacePtr input_interface_ptr;
		glm::vec2 scale_size = glm::vec2(1);
		glm::vec2 mouse_scaled_position = glm::vec2(0);
		InterfaceShader interface_shader;

	public:
		explicit Interface();
		void render(const engine::ScenePtr& scene) override;

		engine::InputInterfacePtr getInputInterface();

		[[nodiscard]] const glm::vec2 &getScaleSize() const;
		void setScaleSize(const glm::vec2 &scaleSize);

		glm::mat4 getModel();
		glm::vec2 getMouseScaledPosition();
	};
}

