#pragma once
#ifndef IA_SLIDER_H
#define IA_SLIDER_H

#include <ianium/testable_ui/ui_element.h>
#include <ianium/ianium.h>

class IANIUM_EXPORT IASlider : public UIElement {
public:
	enum class Orientation { VERTICAL, HORIZONTAL };
	
	IASlider(const int id, const int posX, const int posY, const int w, const int h, const bool active, const char* menu, 
		const float value, const float minValue, const float maxValue, const int rangeSelection, const Orientation orientation) 
		: UIElement(Ianium::UIType::SLIDER, id, posX, posY, w, h, active, menu), value(value), minValue(minValue), 
		maxValue(maxValue), rangeSelection(rangeSelection), orientation(orientation) {}

	float getValue() const { return value; }
	float getMinValue() const { return minValue; }
	float getMaxValue() const { return maxValue; }
	int getRangeSelection() const { return rangeSelection; }
	Orientation getOrientation() const { return orientation; }

private:
	float value;					// Valor actual del slider
	float minValue, maxValue;		// Valor mínimo y maximo del slider
	int rangeSelection;				// Cantidad de valores que se pueden seleccionar en el slider      
	Orientation orientation;		// Orientación del slider (horizontal o vertical)
};
#endif // IA_SLIDER_H