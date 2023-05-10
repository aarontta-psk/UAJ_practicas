#pragma once
#include "UIElement.h"

class Toggle : public UIElement {
private:

    //Estado del Toogle (Pulsado o sin pulsar)
    bool toggleOn;

public:
    Toggle(int id, int posX, int posY, int w, int h, bool active, const std::string& menu): UIElement(id, posX, posY, w, h, active, menu), toggleOn(false) {
    }

    bool getToggleState() const {
        return toggleOn;
    }
};
