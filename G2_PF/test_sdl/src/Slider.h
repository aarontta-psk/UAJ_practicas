#pragma once
#ifndef SLIDER_H
#define SLIDER_H

#include <ianium/testable_ui/slider.h>

#include "HudElement.h"
#include "Image.h"

class Slider : public ianium::Slider, public HudElement {
public:
	enum class Orientation { VERTICAL, HORIZONTAL };

	Slider(SDL_Renderer* renderer, std::string pathRange, std::string pathValue, const uint32_t id, const uint32_t posX, const uint32_t posY, const uint32_t w, const uint32_t h, const bool active,
		const float val, const float minV, const float maxV, const uint32_t range, const Orientation ori);
	virtual ~Slider();

	virtual void render(SDL_Renderer* renderer) override;
	virtual void handleInput(const SDL_Event& i_event);
	virtual void reset();

	virtual std::pair<uint32_t, uint32_t> getPosition() const;
	virtual std::pair<uint32_t, uint32_t> getSize() const;
	virtual bool getEnable() const;

	virtual float getValue() const;

	float getMinValue() const;
	float getMaxValue() const;
	uint32_t getRangeSelection() const;

private:
	float value;					// sldier value
	float minValue, maxValue;		// min & max slider value
	uint32_t rangeSelection;		// slider range      
	Orientation orientation;		// orientation

	float value_original;

	SDL_Rect rect;
	Image* imageRange;
	Image* imageValue;
};
#endif // SLIDER_H