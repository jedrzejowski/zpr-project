/**
 * @file InGameMenu.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "InGameMenu.h"
#include "GameScene.h"

game::InGameMenu::InGameMenu(game::GameScenePtr &scene) :
		Interface() {


	getInputInterface()->getKeyboard()->Escape.onPressed([&] {
		onMenuExit();
	});
}

game::InGameMenuPtr game::InGameMenu::create(game::GameScenePtr &scene) {
	struct trick : InGameMenu {
		trick(game::GameScenePtr &scene) : InGameMenu(scene) {}
	};

	InGameMenuPtr self = std::make_shared<trick>(scene);
	self->initEvents();

	return self;
}

void game::InGameMenu::initEvents() {
	resume_button_ptr = gui::Button::create(this->shared_from_this());
	resume_button_ptr->setText("Wznow gre");
	resume_button_ptr->setPosition(glm::vec2(0, 0.3));
	resume_button_ptr->onClicked([&] {
		onMenuExit();
	});

	save_btn_ptr = gui::Button::create(this->shared_from_this());
	save_btn_ptr->setText("Zapisz i wyjdz");
	save_btn_ptr->setPosition(glm::vec2(0, 0.5));
	save_btn_ptr->onClicked([&] {
		onSaveAndExit();
	});
}
