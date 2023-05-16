#pragma once
#include "HudElement.h"
#include "Image.h"


class Button : public ianium::Button, public HudElement {
public:
	enum class State { PRESSED, HOLD, RELEASED };

	Button(std::string pathPressed, std::string pathReleased, int id, int posXAux, int posYAux, int wAux, int hAux, bool active, SDL_Renderer* renderer) ;
	virtual ~Button();

	//REDEFINICIONES CLASE UUIELEMENT
	// Devuelve la posición (X, Y) del elemento
	virtual std::pair<uint32_t, uint32_t> getPosition() const;
	// Devuelve el tamaño (ancho, alto) del elemento
	virtual std::pair<uint32_t, uint32_t> getSize() const ;
	// Devuelve el estado del elemento
	virtual bool getEnable() const;

	//REDEFINICIONES CLASE BUTTON
	virtual int getStateButton() const;

	virtual void render(SDL_Renderer* renderer) override;

	//TODO AAA METER AQUI QUE EL ESTADO DEL BOTON SEA PRESSED HOLD O RELEASED
	virtual void handleInput(const SDL_Event& i_event);

private:
	//TODO FALTA ESTE ESTADO DE KK
	State buttonState;

	SDL_Rect rect;
	Image* imageReleased;
	Image* imagePressed;
};


