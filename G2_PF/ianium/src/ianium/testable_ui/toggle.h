#pragma once
#ifndef IA_TOGGLE_H
#define IA_TOGGLE_H

#include <ianium/testable_ui/ui_element.h>

namespace ianium {
	class IANIUM_EXPORT Toggle : public UIElement {
	public:
		Toggle(const uint64_t id) : UIElement(UIType::TOGGLE, id) {}
		virtual ~Toggle() = default;

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
		/// Returns toggle's state. States have to be defined by the child class.
		/// A quick suggestion would be to have a marked and unmarked state.
		/// </summary>
		/// <returns>Toggle state</returns>
		virtual bool getToggleState() const = 0;
	};
};
#endif // IA_TOGGLE_H