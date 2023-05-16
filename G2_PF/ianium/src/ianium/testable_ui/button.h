#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <ianium/testable_ui/ui_element.h>

namespace ianium {
	class IANIUM_EXPORT Button : public UIElement {
	public:
		Button(const uint64_t id) : UIElement(UIType::BUTTON, id) {}

		virtual void handleInput(const SDL_Event& i_event) = 0;
		virtual void render(SDL_Renderer* renderer) = 0;

		virtual int getStateButton() const = 0;

		virtual void reset() = 0;
	};
}
#endif // BUTTON_H