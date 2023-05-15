#pragma once
#ifndef TOGGLE_H
#define TOGGLE_H

#include <ianium/testable_ui/ui_element.h>
#include <ianium/ianium.h>

namespace ianium {
	class IANIUM_EXPORT Toggle : public UIElement {
	public:
		Toggle(const int id, const int posX, const int posY, const int w, const int h, const bool active, const char* menu)
			: UIElement(UIType::TOGGLE, id, posX, posY, w, h, active, menu), toggleOn(false) {}        
		
		virtual void handleInput(const SDL_Event& i_event) = 0;
		virtual void render(SDL_Renderer* renderer) = 0;

		bool getToggleState() const { return toggleOn; }

	private:
		bool toggleOn;	// Estado del Toogle (Pulsado o sin pulsar)
	};
};
#endif // IA_TOGGLE_H