#pragma once
#include "HudElement.h"
#include "Image.h"

class Slider : public ianium::Slider, public HudElement {
public:
	enum class Orientation { VERTICAL, HORIZONTAL };

	Slider(std::string pathRange, std::string pathValue, const int id, const int posXAux, const int posYAux, const int wAux, const int hAux, const bool active,
		const float valueAux, const float minValueAux, const float maxValueAux, const int rangeSelectionAux, const Orientation orientationAux, SDL_Renderer* renderer);

	virtual ~Slider();

	//REDEFINICIONES CLASE UIELEMENT
	// Devuelve la posición (X, Y) del elemento
	virtual std::pair<uint32_t, uint32_t> getPosition() const;
	// Devuelve el tamaño (ancho, alto) del elemento
	virtual std::pair<uint32_t, uint32_t> getSize() const;
	// Devuelve el estado del elemento
	virtual bool getEnable() const;

	//REDEFINICIONES CLASE SLIDER
	virtual float getValue() const;
	virtual float getMinValue() const;
	virtual float getMaxValue() const;
	virtual int getRangeSelection() const;

	virtual void render(SDL_Renderer* renderer) override;

	virtual void handleInput(const SDL_Event& i_event);

private:
	float value;					// Valor actual del slider
	float minValue, maxValue;		// Valor mínimo y maximo del slider
	int rangeSelection;				// Cantidad de valores que se pueden seleccionar en el slider      
	Orientation orientation;		// Orientación del slider (horizontal o vertical)

	SDL_Rect rect;
	Image* imageRange;
	Image* imageValue;

};

