#pragma once
#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include <string>

#include <common/macros.h>
#include <ianium/ianium.h>

typedef union SDL_Event;

namespace ianium {
	enum class UIType { BUTTON, TOGGLE, SLIDER };

	class IANIUM_EXPORT UIElement {
	public:
		UIElement(const UIType type, const uint64_t id) : id(id) { Ianium::Instance()->addTestableUIElem(type, this); }

		virtual void handleInput(const SDL_Event& i_event) = 0;
		virtual void render(SDL_Renderer* renderer) = 0;

		// Devuelve la ID del elemento
		virtual uint64_t getID() const { return id; }
		// Devuelve la posición (X, Y) del elemento
		virtual std::pair<uint32_t, uint32_t> getPosition() const = 0;
		// Devuelve el tamaño (ancho, alto) del elemento
		virtual std::pair<uint32_t, uint32_t> getSize() const = 0;
		// Devuelve el estado del elemento
		virtual bool getEnable() const = 0;
		//Resetea el estado del objeto
		virtual void reset() = 0;

	protected:
		uint64_t id;            // ID único del elemento
	};
};
#endif // UI_ELEMENT_H