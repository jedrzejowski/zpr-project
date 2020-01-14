/**
 * @file TriButton.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */
#pragma once

#include "_classdef.h"
#include "src/lib/Signal.hpp"
#include "GuiObject.h"

namespace gui {

	/**
	 * @brief Potrójny przycisk
	 */
	class TriButton : public GuiObject, public VirtualSharePtrObject<TriButton> {
	public:
		using VirtualSharePtrObject<TriButton>::shared_from_this;
		using VirtualSharePtrObject<TriButton>::weak_from_this;
	private:

		glm::vec2 position = glm::vec2(0);
		glm::vec2 size = glm::vec2(1);

		ButtonPtr main_button_ptr;
		ButtonPtr positive_button_ptr;
		ButtonPtr negative_button_ptr;

		explicit TriButton(InterfacePtr &interface);
		explicit TriButton(GuiObjectPtr &parent);
		void constructorTriButton();

		void updateModel();
	public:
		static TriButtonPtr create(InterfacePtr &interface);
		static TriButtonPtr create(GuiObjectPtr &parent);
		~TriButton() override;

		void updateBuffers() override;

		const glm::vec2 &getPosition() const;
		void setPosition(const glm::vec2 &new_position);
		const glm::vec2 &getSize() const;
		void setSize(const glm::vec2 &new_size);

		const ButtonPtr &getNegativeButton() const;
		const ButtonPtr &getMainButton() const;
		const ButtonPtr &getPositiveButton() const;

		void setText(const std::string &negative_text, const std::string &main_text, const std::string &positive_text);

		const Signal<> onMainClick;
		const Signal<> onPositiveClick;
		const Signal<> onNegativeClick;
	};
}


