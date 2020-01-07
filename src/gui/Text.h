#pragma once

#include "src/_classdef.h"
#include "src/lib/Object.hpp"
#include "GuiObject.h"

namespace gui {

	class Text : public GuiObject {
	private:
		std::string content = "Text";

	public:
		explicit Text(InterfacePtr interface);
		explicit Text(GuiObjectPtr parent);

		const std::string &getContent() const;
		void setContent(const std::string &content);

		void updateBuffers() override;
	};
}

