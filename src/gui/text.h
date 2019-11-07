#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"
#include "guiObj.h"

namespace gui {

	class Text : public GuiObject {
	private:
		std::string content;

	public:
		explicit Text(Interface* interface);
		explicit Text(GuiObject* parent);

		const std::string &getContent() const;
		void setContent(const std::string &content);

		void updateBuffers() override;
	};
}

