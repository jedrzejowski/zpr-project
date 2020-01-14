/**
 * @file Scene.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/lib/Object.h"
#include "src/lib/Signal.hpp"

#include "Light.h"
#include "ShaderProgram.h"
#include "Window.h"

namespace engine {

	/**
	 * @brief Klasa sceny
	 *
	 * Klasa Window wyświetla sceny, które mogą się zmieniać w czasie działania programu.
	 * Sceny powinny mieć przynajmniej jeden interfejs wejściowy(obsługa myszki i klawiatury).
	 * Cykl sceny w pętli głównej to: render() -> eventy z InputInterface -> pollEvents()
	 */
	class Scene : public Object, public VirtualSharePtrObject<Scene> {
	public:
		using VirtualSharePtrObject<Scene>::shared_from_this;
		using VirtualSharePtrObject<Scene>::weak_from_this;
	private:
		WindowWPtr window_wptr;
		InputInterfacePtr input_interface_ptr;
	protected:
		Scene();
	public:

		/**
		 * @brief Główna funkcja w której należy renderować scene
		 * @param window
		 */
		virtual void render(WindowPtr& window) = 0;

		WindowWPtr getWindow() const;
		void setWindow(WindowWPtr window);
		bool isInWindow();

		InputInterfacePtr getInputInterface();
		void setInputInterface(InputInterfacePtr interface_ptr);

		virtual void pollEvents() {};

		const Signal<> onRefreshBuffers;
		const Signal<> onWindowChanged;
	};
}
