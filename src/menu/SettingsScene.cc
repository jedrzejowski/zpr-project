/**
 * @file SettingsScene.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "SettingsScene.h"
#include "WelcomeScene.h"

menu::SettingsScene::SettingsScene() {
	logger(4).constructor(this);
}

void menu::SettingsScene::constructorSettingsScene() {
	interface = std::make_shared<gui::Interface>();
	auto input_interface = interface->getInputInterface();
	setInputInterface(interface->getInputInterface());

	input_interface->getKeyboard()->Escape.onPressed([&]{
		if (auto window_ptr = getWindow().lock()) {
			auto newScene = menu::WelcomeScene::create();
			window_ptr->setScene(newScene);
		}
	});

	camera_angle_button = gui::TriButton::create(interface);
	camera_angle_button->setPosition(glm::vec2(0, 0.3));

	chunk_render_button = gui::TriButton::create(interface);
	chunk_render_button->setPosition(glm::vec2(0, 0.5));
}

menu::SettingsScene::~SettingsScene() {
	logger(4).destructor(this);
}

menu::SettingsScenePtr menu::SettingsScene::create() {
	struct Self : public SettingsScene {
	};

	SettingsScenePtr self = std::make_shared<Self>();
	self->constructorSettingsScene();
	return self;
}

void menu::SettingsScene::render(engine::WindowPtr &window) {
	interface->render(this->shared_from_this());
}
