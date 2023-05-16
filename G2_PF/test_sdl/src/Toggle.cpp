#include "Toggle.h"

Toggle::Toggle(std::string pathToogleOn, std::string pathToogleOff, const int id, const int posXAux, const int posYAux, const int wAux, const int hAux, const bool active, SDL_Renderer* renderer)
	: ianium::Toggle(id), HudElement(posXAux, posYAux, wAux, hAux, active) {

	toggleOn = false;
	imageOn = new Image(pathToogleOn, renderer);
	imageOff = new Image(pathToogleOff, renderer);
}

Toggle::~Toggle()
{
	delete imageOn;
	delete imageOff;
}

std::pair<uint32_t, uint32_t> Toggle::getPosition() const
{
	return std::make_pair(posX, posY);
}

std::pair<uint32_t, uint32_t> Toggle::getSize() const
{
	return std::make_pair(width, height);
}

bool Toggle::getEnable() const
{
	return isActive;
}

bool Toggle::getToggleState() const
{
	return toggleOn;
}

void Toggle::render(SDL_Renderer* renderer)
{
	rect = { (int)posX,(int)posY,(int)width,(int)height };

	//Activao
	if (toggleOn)
		imageOn->render(rect, renderer);

	//Desactivado
	else
		imageOff->render(rect, renderer);
}

void Toggle::handleInput(const SDL_Event& i_event)
{

	if (i_event.type != SDL_MOUSEBUTTONDOWN)
		return;

	int x = i_event.button.x;
	int y = i_event.button.y;
	int n_clicks = i_event.button.clicks;

	// Obtener el estado actual del rat�n
		/*int mouseX, mouseY;
		Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);*/

		// Verificar si se ha pulsado el bot�n izquierdo del rat�n
		//if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			// Verificar si el rat�n est� dentro de los l�mites del bot�n
	if (x >= posX && x < posX + width && y >= posY && y < posY + height) {
		// Si el bot�n no estaba presionado previamente
		//if (!buttonPressed) {
			// Cambiar el valor del booleano toogleOn
		for (int i = 0; i < n_clicks; i++)
			toggleOn = !toggleOn;
		// Establecer el estado de bot�n como presionado
		//buttonPressed = true;
	//}
	}
	//}
	//else {
	//	// Si se ha soltado el bot�n, establecer el estado de bot�n como no presionado
	//	buttonPressed = false;
	//}
}

void Toggle::reset()
{
	toggleOn = false;
}
