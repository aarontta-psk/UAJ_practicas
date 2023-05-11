#pragma once
#ifndef IA_BUTTON_H
#define IA_BUTTON_H

#include <ui/ui_element.h>

class IANIUM_EXPORT IAButton : public UIElement {
private:
    enum State { PRESSED,HOLD,RELEASED };

    State buttonState;

public:
    IAButton(int id, int posX, int posY, int w, int h, bool active, const std::string& menu): UIElement(id, posX, posY, w, h, active, menu), buttonState(RELEASED) {
    }

    State getStateButton() const {
        return buttonState;
    }
};
#endif // IA_BUTTON_H