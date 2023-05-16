#pragma once

#include <SDL2/SDL.h>

/*Ianium*/
#include <ianium/testable_ui/button.h>
#include <ianium/testable_ui/slider.h>
#include <ianium/testable_ui/toggle.h>

#include <ianium/ianium.h>
/*Ianium*/

class HudElement {
public:
	HudElement(int posXAux, int posYAux, int widthAux, int heightAux, bool isActiveAux) :posX(posXAux), posY(posYAux), width(widthAux), height(heightAux), isActive(isActiveAux) {};
	virtual ~HudElement() = default;

	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void handleInput(const SDL_Event& event) {};

protected:
	uint32_t posX, posY;    // Posición X e Y del elemento
	uint32_t width, height; // Ancho y alto del elemento                
	bool isActive;          // Estado del elemento (Activado o desactivado)         
};