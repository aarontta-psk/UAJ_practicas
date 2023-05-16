#pragma once
#ifndef IA_SLIDER_H
#define IA_SLIDER_H

#include <ianium/testable_ui/ui_element.h>

namespace ianium {
	class IANIUM_EXPORT Slider : public UIElement {
	public:
		Slider(const uint64_t id) : UIElement(UIType::SLIDER, id) {}

		/// <summary>
		/// Defines UI element's behaviour upon processing SDL Events.
		/// Has to be redefined so the functional testing may work.
		/// </summary>
		/// <param name="i_event">SDL event to be processed</param>
		virtual void handleInput(const SDL_Event& i_event) = 0;
		/// <summary>
		/// Defines ui element's rendering behaviour.
		/// Has to be redefined so the visual testing may work.
		/// </summary>
		/// <param name="renderer">SDL renderer</param>
		virtual void render(SDL_Renderer* renderer) = 0;
		/// <summary>
		/// Reset the UI element to its original state
		/// </summary>
		virtual void reset() = 0;

		/// <summary>
		/// Returns slider's internal value, between 0 and 1.
		/// Be careful to limit this value to that given threshold.
		/// </summary>
		/// <returns>Internal slider value</returns>
		virtual float getValue() const = 0;
	};
};
#endif // IA_SLIDER_H