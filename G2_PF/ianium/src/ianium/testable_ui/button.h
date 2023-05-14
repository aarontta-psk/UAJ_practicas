#pragma once
#ifndef IA_BUTTON_H
#define IA_BUTTON_H

#include <ianium/testable_ui/ui_element.h>

namespace ianium {
    class IANIUM_EXPORT Button : public UIElement {
    public:
        enum class State { PRESSED, HOLD, RELEASED };

        Button(const int id, const int posX, const int posY, const int w, const int h, const bool active, const char* menu)
            : UIElement(Ianium::UIType::BUTTON, id, posX, posY, w, h, active, menu), buttonState(State::RELEASED) {}

        State getStateButton() const { return buttonState; }

    private:
        State buttonState;
    };
}
#endif // IA_BUTTON_H