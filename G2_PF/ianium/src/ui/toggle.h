#pragma once
#ifndef IA_TOGGLE_H
#define IA_TOGGLE_H

#include <ui/ui_element.h>

class IANIUM_EXPORT IAToggle : public UIElement {
private:

	//Estado del Toogle (Pulsado o sin pulsar)
	bool toggleOn;

public:
	IAToggle(int id, int posX, int posY, int w, int h, bool active, const std::string& menu) : UIElement(id, posX, posY, w, h, active, menu), toggleOn(false) {
	}

	bool getToggleState() const {
		return toggleOn;
	}
};
#endif // IA_TOGGLE_H