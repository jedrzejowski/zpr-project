/**
 * @file SettingsScene.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "SettingsScene.h"
#include "WelcomeScene.h"
#include "src/lib/AppSettings.h"

menu::SettingsScene::SettingsScene() {
	logger(4).constructor(this);
}

void menu::SettingsScene::constructorSettingsScene() {
	static auto &app_settings = AppSettings::get();


	interface = std::make_shared<gui::Interface>();
	auto input_interface = interface->getInputInterface();
	setInputInterface(interface->getInputInterface());

	input_interface->getKeyboard()->Escape.onPressed([&] { backToWelcomeScene(); });

	newNumberSettings(app_settings.playerCameraAngle, boost::format{"Kat kamery: %1%"}, 1.f, 180.f);
	newNumberSettings(app_settings.chunkRenderDistance, boost::format{"Zasieg renderowania: %1%"}, 2.f, 100.f);


	auto return_button = gui::Button::create(interface);
	return_button->setText("Wroc");
	return_button->setPosition(glm::vec2(0, new_settings_position));
	return_button->onClicked([&] { backToWelcomeScene(); });
	new_settings_position += 0.2;
	children.push_back(return_button);
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

template<typename T>
void menu::SettingsScene::newNumberSettings(const LiveData<T> &live_data,
											boost::basic_format<char> title,
											T min_value,
											T max_value) {
	auto button = gui::TriButton::create(interface);
	auto button_wptr = button->weak_from_this();
	children.push_back(button);

	button->setText("-", str(title % live_data.get()), "+");
	button->getMainButton()->setState(gui::ButtonState::Disabled);
	button->getMainButton()->setTextSize(0.4);

	button->setPosition(glm::vec2(0, new_settings_position));
	new_settings_position += 0.2;

	live_data.onChange(this, [button_wptr, title](const float &old_value, const float &new_value) {
		if (auto button_ptr = button_wptr.lock()) {
			auto title_noconst = title;
			button_ptr->getMainButton()->setText(str(title_noconst % new_value));
		}
	});

	button->onPositiveClick([&] {
		live_data.set(live_data.get() + 1);
	});

	button->onNegativeClick([&] {
		live_data.set(live_data.get() - 1);
	});
}

void menu::SettingsScene::backToWelcomeScene() {
	if (auto window_ptr = getWindow().lock()) {
		auto newScene = menu::WelcomeScene::create();
		window_ptr->setScene(newScene);
	}
}
