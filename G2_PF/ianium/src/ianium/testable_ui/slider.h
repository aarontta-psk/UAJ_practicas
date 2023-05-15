#pragma once
#ifndef SLIDER_H
#define SLIDER_H

#include <ianium/testable_ui/ui_element.h>
#include <ianium/ianium.h>

namespace ianium {
	class IANIUM_EXPORT Slider : public UIElement {
	public:
		enum class Orientation { VERTICAL, HORIZONTAL };

		Slider(const int id, const int posX, const int posY, const int w, const int h, const bool active, const char* menu,
			const float value, const float minValue, const float maxValue, const int rangeSelection, const Orientation orientation)
			: UIElement(UIType::SLIDER, id, posX, posY, w, h, active, menu), value(value), minValue(minValue),
			maxValue(maxValue), rangeSelection(rangeSelection), orientation(orientation) {}

		virtual void handleInput(const SDL_Event& i_event) = 0;
		virtual void render(SDL_Renderer* renderer) = 0;

		float getValue() const { return value; }
		float getMinValue() const { return minValue; }
		float getMaxValue() const { return maxValue; }
		int getRangeSelection() const { return rangeSelection; }
		Orientation getOrientation() const { return orientation; }

	private:
		float value;					// Valor actual del slider
		float minValue, maxValue;		// Valor m�nimo y maximo del slider
		int rangeSelection;				// Cantidad de valores que se pueden seleccionar en el slider      
		Orientation orientation;		// Orientaci�n del slider (horizontal o vertical)
	};
};
#endif // IA_SLIDER_H