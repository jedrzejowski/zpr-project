#pragma once

#include <list>
#include "src/_classdef.h"
#include "src/lib/object.h"
#include "src/engine/Engine.h"

namespace gui {
	struct InterfaceItem {
		glm::mat4 model;
		GuiObject *object;
	};

	class Interface : public Object, public engine::Abs3DObj {
	private:
		std::list<InterfaceItem *> objects;

		engine::Shader *shader = nullptr;
		const engine::Texture *texture = nullptr;

	protected:
		void updateBuffers() override;

	public:
		explicit Interface(engine::Scene *parent = nullptr);
		void render(const engine::Scene *scene) override;

		void addObject(glm::vec2 position, glm::vec2 size, GuiObject *object);
		void addObject(glm::mat4 model, GuiObject *object);
		void removeObject(GuiObject *object);
	};
}

