#pragma once
#ifndef IA_UI_ELEMENT_H
#define IA_UI_ELEMENT_H

#include <string>

#include <common/macros.h>
#include <ianium/ianium.h>

typedef union SDL_Event;

namespace ianium {
	enum class UIType { BUTTON, TOGGLE, SLIDER };

	class IANIUM_EXPORT UIElement {
	public:
		UIElement(const UIType type, const uint64_t id) : id(id) { Ianium::Instance()->addTestableUIElem(type, this); }
		virtual ~UIElement() = default;

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
		/// Returns UI element's ID value
		/// </summary>
		/// <returns>ID value</returns>
		virtual uint64_t getID() const { return id; }
		/// <summary>
		/// Returns UI element's position in the X and Y axis.
		/// Has to be redefined by the child class.
		/// </summary>
		/// <returns>Position in the X and Y axis</returns>
		virtual std::pair<uint32_t, uint32_t> getPosition() const = 0;
		/// <summary>
		/// Returns UI element's dimensions in the X and Y axis.
		/// Has to be redefined by the child class.
		/// </summary>
		/// <returns>Dimension in the X and Y axis</returns>
		virtual std::pair<uint32_t, uint32_t> getSize() const = 0;
		/// <summary>
		/// Returns if UI element is enabled or disabled.
		/// Has to be redefined by the child class.
		/// </summary>
		/// <returns>Enable state</returns>
		virtual bool getEnable() const = 0;

	protected:
		uint64_t id; // unique ID
	};
};
#endif // IA_UI_ELEMENT_H