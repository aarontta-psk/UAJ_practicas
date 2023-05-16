#include "Slider.h"

Slider::Slider(SDL_Renderer* renderer, std::string pathRange, std::string pathValue, const uint32_t id,
	const uint32_t posX, const uint32_t posY, const uint32_t w, const uint32_t h, const bool active,
	const float val, const float minV, const float maxV, const uint32_t range, const Orientation ori)
	: ianium::Slider(id), HudElement(posX, posY, w, h, active) {
	value, value_original = val;
	minValue = minV;
	maxValue = maxV;
	rangeSelection = range;
	orientation = ori;

	imageRange = new Image(pathRange, renderer);
	imageValue = new Image(pathValue, renderer);
}

Slider::~Slider() {
	delete imageRange;
	delete imageValue;
}

void Slider::render(SDL_Renderer* renderer) {
	rect = { (int)posX, (int)posY, (int)width, (int)height };
	imageRange->render(rect, renderer);

	if (orientation == Orientation::HORIZONTAL)
		rect = { (int)posX + ((int)value * (int)width / (int)maxValue), (int)posY, (int)(width / rangeSelection), (int)height };
	else
		rect = { (int)posX, (int)posY + ((int)value * (int)height / (int)maxValue), (int)width, (int)(height / rangeSelection) };

	imageValue->render(rect, renderer);
}

void Slider::handleInput(const SDL_Event& i_event)
{
	if (i_event.type != SDL_MOUSEBUTTONDOWN)
		return;

	int x = i_event.button.x;
	int y = i_event.button.y;

	if (x >= posX && x < posX + width && y >= posY && y < posY + height) {
		float newValue;
		if (orientation == Orientation::HORIZONTAL)
			newValue = (x - posX) * maxValue / width;
		else
			newValue = (y - posY) * maxValue / height;

		value = newValue;

		if (value < minValue)
			value = minValue;
		else if (value > maxValue - (width / rangeSelection))
			value = maxValue - (maxValue / rangeSelection);
	}
}

void Slider::reset() {
	value = value_original;
}

std::pair<uint32_t, uint32_t> Slider::getPosition() const { return std::make_pair(posX, posY); }

std::pair<uint32_t, uint32_t> Slider::getSize() const {	return std::make_pair(width, height); }

bool Slider::getEnable() const { return isActive; }

float Slider::getValue() const { return value; }

float Slider::getMinValue() const { return minValue; }

float Slider::getMaxValue() const { return maxValue; }

uint32_t Slider::getRangeSelection() const { return rangeSelection; }