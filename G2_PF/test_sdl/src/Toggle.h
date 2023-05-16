#pragma once
#ifndef TOGGLE_H
#define TOGGLE_H

#include <ianium/testable_ui/toggle.h>

#include "HudElement.h"
#include "Image.h"

class Toggle : public ianium::Toggle, public HudElement {
public:
	Toggle(SDL_Renderer* renderer, const std::string pathToogleOn, const std::string pathToogleOff, const uint64_t id,
		const uint32_t posX, const uint32_t posY, const uint32_t w, const uint32_t h, const bool active);
	virtual ~Toggle();

	virtual void render(SDL_Renderer* renderer) override;
	virtual void handleInput(const SDL_Event& i_event);
	virtual void reset();

	virtual std::pair<uint32_t, uint32_t> getPosition() const;
	virtual std::pair<uint32_t, uint32_t> getSize() const;
	virtual bool getEnable() const;

	virtual bool getToggleState() const;

private:
	bool toggleOn;

	SDL_Rect rect;
	Image* imageOn;
	Image* imageOff;
};
#endif // TOGGLE_H