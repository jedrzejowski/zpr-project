#pragma once

#include <list>
#include "src/_classdef.h"
#include "src/lib/object.h"
#include "src/engine/Engine.h"

namespace gui {
	struct InterfaceItem {
		glm::vec3 position;
		GuiObject *object;
	};

	class Interface : public Object, public engine::Abs3DObj {
	private:
		std::list<InterfaceItem *> objects;

		engine::Shader *shader;
		const engine::Texture *texture;

		bool needBufferRefresh = true;

	public:
		Interface(engine::Scene *parent = nullptr);
		void render(engine::Scene *scene);

		void addObject(glm::vec3 position, GuiObject *object);
		void removeObject(GuiObject *object);

		void refreshBuffers();
	};
}

