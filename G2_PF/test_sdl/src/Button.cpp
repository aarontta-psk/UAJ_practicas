#include "Button.h"

Button::Button(std::string pathPressed, std::string pathReleased, int id, int posXAux, int posYAux, int wAux, int hAux, bool active, SDL_Renderer* renderer) : ianium::Button(id), HudElement(posXAux, posYAux, wAux, hAux, active)
{
		buttonState = State::RELEASED;
		imagePressed = new Image(pathPressed, renderer);
		imageReleased = new Image(pathReleased, renderer);
}

Button::~Button(){
	delete imagePressed;
	delete imageReleased;
}

std::pair<uint32_t, uint32_t> Button::getPosition() const
{
	return std::make_pair(posX, posY);
}

std::pair<uint32_t, uint32_t> Button::getSize() const
{
	return std::make_pair(width, height);
}

bool Button::getEnable() const
{
	return isActive;
}

int Button::getStateButton() const
{
	return (int)buttonState;
}

void Button::render(SDL_Renderer* renderer)
{
	rect = { (int)posX,(int)posY,(int)width,(int)height };

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

	if (x >= posX && x < posX + width && y >= posY && y < posY + height) {
		if (i_event.type == SDL_MOUSEBUTTONDOWN) {
			buttonState = State::PRESSED;
		}
	}
	if (i_event.type == SDL_MOUSEBUTTONUP) {
		buttonState = State::RELEASED;
	}
	//}
	//else {
	//	// Si se ha soltado el bot�n, establecer el estado de bot�n como no presionado
	//	buttonPressed = false;
	//}
}
