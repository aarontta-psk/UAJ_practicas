#pragma once
#ifndef IA_SLIDER_H
#define IA_SLIDER_H

#include <ui/ui_element.h>

class IANIUM_EXPORT IASlider : public UIElement {
private:
	// Valor actual del slider
	int value;

	// Valor mínimo y maximo del slider
	int minValue,maxValue;

	// Orientación del slider (horizontal o vertical)
	std::string orientation;

	// Cantidad de valores que se pueden seleccionar en el slider
	int rangeSelection;         

public:
	IASlider(int id, int posX, int posY, int w, int h, bool active, const std::string& menu,int value, int minValue, int maxValue, const std::string& orientation, int rangeSelection):
		UIElement(id, posX, posY, w, h, active, menu), value(value), minValue(minValue), maxValue(maxValue), orientation(orientation), rangeSelection(rangeSelection) {
	}

	int getValue() {
		return value;
	}

	int getMinValue() const {
		return minValue;
	}

	int getMaxValue() const {
		return maxValue;
	}

	std::string getOrientation() const {
		return orientation;
	}

	int getRangeSelection() const {
		return rangeSelection;
	}
};
#endif // IA_SLIDER_H