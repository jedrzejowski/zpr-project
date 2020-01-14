/**
 * @file SettingsScene.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/gui/Interface.h"
#include <boost/format.hpp>

namespace menu {

	/**
	 * @brief Scena z ustawieniami użytkownika
	 */
	class SettingsScene : public engine::Scene, public VirtualSharePtrObject<SettingsScene> {
	public:
		using VirtualSharePtrObject<SettingsScene>::shared_from_this;
		using VirtualSharePtrObject<SettingsScene>::weak_from_this;
	private:
		gui::InterfacePtr interface;
		std::vector<gui::GuiObjectPtr> children;
		float new_settings_position = 0.1;

		explicit SettingsScene();
		void constructorSettingsScene();

		template<typename T>
		void newNumberSettings(
				const LiveData<T>& live_data,
				boost::basic_format<char> title, // nie ma referencji aby ni było błędów l-value i r-value
				T min_value,
				T max_value
		);

		void backToWelcomeScene();
	public:
		static SettingsScenePtr create();
		~SettingsScene() override;
		void render(engine::WindowPtr &window) override;
	};
}