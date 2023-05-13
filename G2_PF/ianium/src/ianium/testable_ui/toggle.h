#pragma once
#ifndef IA_TOGGLE_H
#define IA_TOGGLE_H

#include <ianium/testable_ui/ui_element.h>
#include <ianium/ianium.h>

class IANIUM_EXPORT IAToggle : public UIElement {
public:
	IAToggle(const int id, const int posX, const int posY, const int w, const int h, const bool active, const char* menu)
		: UIElement(Ianium::UIType::TOGGLE, id, posX, posY, w, h, active, menu), toggleOn(false) {}

	bool getToggleState() const { return toggleOn; }

private:
	bool toggleOn;	// Estado del Toogle (Pulsado o sin pulsar)
};
#endif // IA_TOGGLE_H