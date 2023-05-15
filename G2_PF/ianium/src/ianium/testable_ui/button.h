#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <ianium/testable_ui/ui_element.h>

namespace ianium {
    class IANIUM_EXPORT Button : public UIElement {
    public:
        enum class State { PRESSED, HOLD, RELEASED };

        Button(const int id, const int posX, const int posY, const int w, const int h, const bool active, const char* menu)
            : UIElement(UIType::BUTTON, id, posX, posY, w, h, active, menu), buttonState(State::RELEASED) {}

        virtual void handleInput(const SDL_Event& i_event) = 0;
        virtual void render(SDL_Renderer* renderer) = 0;

        State getStateButton() const { return buttonState; }

    private:
        State buttonState;
    };
}
#endif // IA_BUTTON_H