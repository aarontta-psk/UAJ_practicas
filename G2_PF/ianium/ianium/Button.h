#pragma once
#include "UIElement.h"

class Button : public UIElement {
private:
    enum State { PRESSED,HOLD,RELEASED };

    State buttonState;

public:
    Button(int id, int posX, int posY, int w, int h, bool active, const std::string& menu): UIElement(id, posX, posY, w, h, active, menu), buttonState(RELEASED) {
    }

    State getStateButton() const {
        return buttonState;
    }
};