#pragma once
#ifndef TOGGLE_H
#define TOGGLE_H

#include <ianium/testable_ui/ui_element.h>
#include <ianium/ianium.h>

namespace ianium {
	class IANIUM_EXPORT Toggle : public UIElement {
	public:
		Toggle(const uint64_t id): UIElement(UIType::TOGGLE, id) {}

		virtual void handleInput(const SDL_Event& i_event) = 0;
		virtual void render(SDL_Renderer* renderer) = 0;

		virtual bool getToggleState() const = 0;
	};
};
#endif // TOGGLE_H