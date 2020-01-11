/**
 * @file Text.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

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
		void setContent(const std::string &new_content);

		float getContentLength() const;

		void updateBuffers() override;

		const Signal<const std::string &, const std::string &> onContentChanged;

		enum HorizontalAlign {
			Left,
			Center,
			Right
		};
	};
}

