#pragma once
#include "HudElement.h"
#include "Image.h"

class Toggle : public ianium::Toggle, public HudElement {
public:
	Toggle(std::string pathToogleOn, std::string pathToogleOff, const int id, const int posXAux, const int posYAux, const int wAux, const int hAux, const bool active,
		SDL_Renderer* renderer);

	virtual ~Toggle();

	//REDEFINICIONES CLASE UIELEMENT
	// Devuelve la posición (X, Y) del elemento
	virtual std::pair<uint32_t, uint32_t> getPosition() const;
	// Devuelve el tamaño (ancho, alto) del elemento
	virtual std::pair<uint32_t, uint32_t> getSize() const;
	// Devuelve el estado del elemento
	virtual bool getEnable() const;

	//REDEFINICIONES CLASE TOGGLE
	virtual bool getToggleState() const;

	virtual void render(SDL_Renderer* renderer) override;

	virtual void handleInput(const SDL_Event& i_event);

	virtual void reset();

private:
	SDL_Rect rect;
	bool toggleOn;

	Image* imageOn;
	Image* imageOff;
};

