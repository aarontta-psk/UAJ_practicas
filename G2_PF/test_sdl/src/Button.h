#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <ianium/testable_ui/button.h>

#include "HudElement.h"
#include "Image.h"

class Button : public ianium::Button, public HudElement {
public:
	enum class State : uint32_t { PRESSED, HOLD, RELEASED };

	Button(SDL_Renderer* renderer, std::string pathPressed, std::string pathReleased, const uint64_t id, 
		const uint32_t posX, const uint32_t posY, const uint32_t w, const uint32_t h, const bool active);
	virtual ~Button();

	virtual void render(SDL_Renderer* renderer) override;
	virtual void handleInput(const SDL_Event& i_event);
	virtual void reset();

	virtual std::pair<uint32_t, uint32_t> getPosition() const;
	virtual std::pair<uint32_t, uint32_t> getSize() const;
	virtual bool getEnable() const;

	virtual uint32_t getStateButton() const;

private:
	State buttonState;

	SDL_Rect rect;
	Image* imageReleased;
	Image* imagePressed;
};
#endif // BUTTON_H