#include "Button.h"

Button::Button(SDL_Renderer* renderer, std::string pathPressed, std::string pathReleased, const uint64_t id,
	const uint32_t posX, const uint32_t posY, const uint32_t w, const uint32_t h, const bool active) 
	: ianium::Button(id), HudElement(posX, posY, w, h, active) {
		buttonState = State::RELEASED;
		imagePressed = new Image(pathPressed, renderer);
		imageReleased = new Image(pathReleased, renderer);
}

Button::~Button(){
	delete imagePressed;
	delete imageReleased;
}

void Button::render(SDL_Renderer* renderer) {
	rect = { (int)posX, (int)posY, (int)width, (int)height };

	if (buttonState == State::RELEASED)
		imageReleased->render(rect, renderer);
	else if (buttonState == State::PRESSED)
		imagePressed->render(rect, renderer);
}

void Button::handleInput(const SDL_Event& i_event)
{
	int x = i_event.button.x;
	int y = i_event.button.y;
	int n_clicks = i_event.button.clicks;

	if (x >= posX && x < posX + width && y >= posY && y < posY + height)
		if (i_event.type == SDL_MOUSEBUTTONDOWN)
			buttonState = State::PRESSED;
	if (i_event.type == SDL_MOUSEBUTTONUP)
		buttonState = State::RELEASED;
}

void Button::reset() {
	buttonState = State::RELEASED;
}

std::pair<uint32_t, uint32_t> Button::getPosition() const { return std::make_pair(posX, posY); }

std::pair<uint32_t, uint32_t> Button::getSize() const { return std::make_pair(width, height); }

bool Button::getEnable() const { return isActive; }

uint32_t Button::getStateButton() const { return (uint32_t)buttonState; }


//--------------------Wrong one
WrongButton::WrongButton(SDL_Renderer* renderer, std::string pathPressed, std::string pathReleased, const uint64_t id,
	const uint32_t posX, const uint32_t posY, const uint32_t w, const uint32_t h, const bool active)
	: ianium::Button(id), HudElement(posX, posY, w, h, active) {
	buttonState = State::RELEASED;
	imagePressed = new Image(pathPressed, renderer);
	imageReleased = new Image(pathReleased, renderer);
}

WrongButton::~WrongButton() {
	delete imagePressed;
	delete imageReleased;
}

void WrongButton::render(SDL_Renderer* renderer) {
	rect = { (int)posX, (int)posY, (int)width, (int)height };

	// doesn't use the released image
	imagePressed->render(rect, renderer);
}

void WrongButton::handleInput(const SDL_Event& i_event)
{
	// empty
}

void WrongButton::reset() {
	buttonState = State::RELEASED;
}

std::pair<uint32_t, uint32_t> WrongButton::getPosition() const { return std::make_pair(posX, posY); }

std::pair<uint32_t, uint32_t> WrongButton::getSize() const { return std::make_pair(width, height); }

bool WrongButton::getEnable() const { return isActive; }

uint32_t WrongButton::getStateButton() const { return (uint32_t)buttonState; }