#pragma once
#ifndef HUD_ELEMENT_H
#define HUD_ELEMENT_H

#include <SDL2/SDL.h>

#include <ianium/ianium.h>

class HudElement {
public:
	HudElement(int posXAux, int posYAux, int widthAux, int heightAux, bool isActiveAux) 
		: posX(posXAux), posY(posYAux), width(widthAux), height(heightAux), isActive(isActiveAux) {};
	virtual ~HudElement() = default;

	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void handleInput(const SDL_Event& event) = 0;

protected:
	uint32_t posX, posY;    // X and Y position of the element
	uint32_t width, height; // width and height of the element                
	bool isActive;          // active state of the element         
};
#endif // HUD_ELEMENT_H