#include "Slider.h"

Slider::Slider(std::string pathRange, std::string pathValue, const int id, const int posXAux, const int posYAux, const int wAux, const int hAux, const bool active, const float valueAux, const float minValueAux, const float maxValueAux, const int rangeSelectionAux, const Orientation orientationAux, SDL_Renderer* renderer)
	: ianium::Slider(id), HudElement(posXAux, posYAux, wAux, hAux, active) {

	value, value_original = valueAux;
	minValue, minValue_original = minValueAux;
	maxValue, maxValue_original = maxValueAux;
	rangeSelection, rangeSelection_original= rangeSelectionAux;
	orientation, orientation_original = orientationAux;

	imageRange = new Image(pathRange, renderer);
	imageValue = new Image(pathValue, renderer);
}

Slider::~Slider()
{
	delete imageRange;
	delete imageValue;
}

std::pair<uint32_t, uint32_t> Slider::getPosition() const
{
	return std::make_pair(posX, posY);
}

std::pair<uint32_t, uint32_t> Slider::getSize() const
{
	return std::make_pair(width, height);
}

bool Slider::getEnable() const
{
	return isActive;
}

float Slider::getValue() const
{
	return value;
}

float Slider::getMinValue() const
{
	return minValue;
}

float Slider::getMaxValue() const
{
	return maxValue;
}

int Slider::getRangeSelection() const
{
	return rangeSelection;
}

void Slider::render(SDL_Renderer* renderer)
{
	//Dibujamos su rango
	rect = { (int)posX,(int)posY,(int)width,(int)height };

	imageRange->render(rect, renderer);

	//Y ahora el boton deslizante
	if (orientation == Orientation::HORIZONTAL)
		rect = { (int)posX + ((int)value * (int)width / (int)maxValue),(int)posY,(int)width / rangeSelection,(int)height };
	else
		rect = { (int)posX ,(int)posY + ((int)value * (int)height / (int)maxValue),(int)width,(int)height / rangeSelection };

	imageValue->render(rect, renderer);
}

void Slider::handleInput(const SDL_Event& i_event)
{

	if (i_event.type != SDL_MOUSEBUTTONDOWN)
		return;

	int x = i_event.button.x;
	int y = i_event.button.y;

	// Verificamos si el ratón está dentro de los límites del slider
	if (x >= posX && x < posX + width && y >= posY && y < posY + height) {
		// Calculamos el nuevo valor del slider según la posición del ratón
		float newValue;
		if (orientation == Orientation::HORIZONTAL) {
			newValue = (x - posX) * maxValue / width;
		}
		else {
			newValue = (y - posY) * maxValue / height;
		}

		// Actualizar el valor del slider
		value = newValue;

		// Asegurarse de que el valor esté dentro del rango permitido
		if (value < minValue) {
			value = minValue;
		}
		else if (value > maxValue - (width / rangeSelection)) {
			value = maxValue - (maxValue / rangeSelection);
		}
	}
}

void Slider::reset()
{
	value = value_original;
	minValue = minValue_original;
	maxValue = maxValue_original;
	rangeSelection = rangeSelection_original;
	orientation = orientation_original;
}
