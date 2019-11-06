#pragma once

#include <list>
#include "src/_classdef.h"
#include "src/lib/object.h"
#include "src/engine/Engine.h"

namespace gui {

	class Interface : public Object, public engine::Abs3DObj {
	private:
		engine::InputInterface *inputInterface;
		engine::Scene *scene;

		engine::Shader *shader = nullptr;
		const engine::Texture *texture = nullptr;

		glm::vec2 scaleSize = glm::vec2(1);

		glm::vec2 mouseScaledPosition = glm::vec2(0);
	public:
		explicit Interface(engine::Scene *scene);
		void render(const engine::Scene *scene) override;

		engine::InputInterface *getInputInterface() const;
		engine::Scene *getScene() const;

		const glm::vec2 &getScaleSize() const;
		void setScaleSize(const glm::vec2 &scaleSize);

		glm::mat4 getModel();
		glm::vec2 getMouseScaledPosition();
	};
}

