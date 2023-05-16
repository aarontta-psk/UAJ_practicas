#pragma once
#ifndef SLIDER_H
#define SLIDER_H

#include <ianium/testable_ui/ui_element.h>
#include <ianium/ianium.h>

namespace ianium {
	class IANIUM_EXPORT Slider : public UIElement {
	public:
		Slider(const uint64_t id) : UIElement(UIType::SLIDER, id) {}

		virtual void handleInput(const SDL_Event& i_event) = 0;
		virtual void render(SDL_Renderer* renderer) = 0;

		virtual float getValue() const = 0;
		virtual float getMinValue() const = 0;
		virtual float getMaxValue() const = 0;
		virtual int getRangeSelection() const = 0;

		virtual void reset() = 0;
	};
};
#endif // SLIDER_H