#pragma once

#include <list>
#include "src/_classdef.h"
#include "src/lib/object.h"
#include "src/engine/Engine.h"
#include "interfaceShader.h"

namespace gui {

	class Interface : public Object, public engine::Abs3DObj {
	private:
		engine::InputInterfacePtr inputInterface;
		glm::vec2 scaleSize = glm::vec2(1);
		glm::vec2 mouseScaledPosition = glm::vec2(0);
		InterfaceShader interfaceShader;

	public:
		explicit Interface();
		void render(const engine::ScenePtr scene) override;

		engine::InputInterfacePtr getInputInterface();

		const glm::vec2 &getScaleSize() const;
		void setScaleSize(const glm::vec2 &scaleSize);

		glm::mat4 getModel();
		glm::vec2 getMouseScaledPosition();
	};
}

