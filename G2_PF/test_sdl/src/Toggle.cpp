#include "Toggle.h"

Toggle::Toggle(SDL_Renderer* renderer, const std::string pathToogleOn, const std::string pathToogleOff, const uint64_t id,
	const uint32_t posX, const uint32_t posY, const uint32_t w, const uint32_t h, const bool active)
	: ianium::Toggle(id), HudElement(posX, posY, w, h, active) {
	toggleOn = false;
	imageOn = new Image(pathToogleOn, renderer);
	imageOff = new Image(pathToogleOff, renderer);
}

Toggle::~Toggle() {
	delete imageOn;
	delete imageOff;
}

void Toggle::render(SDL_Renderer* renderer) {
	rect = { (int)posX, (int)posY, (int)width, (int)height };

	if (toggleOn)
		imageOn->render(rect, renderer);
	else
		imageOff->render(rect, renderer);
}

void Toggle::handleInput(const SDL_Event& i_event) {
	if (i_event.type != SDL_MOUSEBUTTONDOWN)
		return;

	int x = i_event.button.x;
	int y = i_event.button.y;
	int n_clicks = i_event.button.clicks;

	if (x >= posX && x < posX + width && y >= posY && y < posY + height)
		for (int i = 0; i < n_clicks; i++)
			toggleOn = !toggleOn;
}

void Toggle::reset() {
	toggleOn = false;
}

std::pair<uint32_t, uint32_t> Toggle::getPosition() const { return std::make_pair(posX, posY); }

std::pair<uint32_t, uint32_t> Toggle::getSize() const { return std::make_pair(width, height);  }

bool Toggle::getEnable() const { return isActive; }

bool Toggle::getToggleState() const { return toggleOn; }