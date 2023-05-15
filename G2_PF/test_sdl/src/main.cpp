#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <ianium/testable_ui/button.h>
#include <ianium/testable_ui/slider.h>
#include <ianium/testable_ui/toggle.h>

#include <ianium/ianium.h>
#include <iostream>
#include <fstream>

#include <list>

class HudElement {
public:
	HudElement() {};
	~HudElement() = default;

	virtual void render(SDL_Renderer* renderer) {}
	virtual void update(int x, int y, int n_clicks) {}
	virtual void processInput(SDL_Event* event) {}

};

class Button : public ianium::Button, public HudElement {
public:
	Button(int id, int posXAux, int posYAux, int wAux, int hAux, bool active, const char* menu) : ianium::Button(id, posX, posY, w, h, active, menu) {
		posX = posXAux;
		posY = posYAux;
		w = wAux;
		h = hAux;
	};
	~Button() = default;

	int posX, posY, w, h;

	SDL_Rect rect;

	void render(SDL_Renderer* renderer) override {

		//Cuadrado rosita
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

		rect = { posX,posY,w,h };
		SDL_RenderFillRect(renderer, &rect);
	}
};

class Slider : public ianium::Slider, public HudElement {
public:
	Slider(const int id, const int posXAux, const int posYAux, const int wAux, const int hAux, const bool active, const char* menu,
		const float valueAux, const float minValueAux, const float maxValueAux, const int rangeSelectionAux, const Orientation orientationAux)
		: ianium::Slider(id, posX, posY, w, h, active, menu, valueAux, minValueAux, maxValueAux, rangeSelectionAux, orientationAux) {
		posX = posXAux;
		posY = posYAux;
		w = wAux;
		h = hAux;
		rangeSelection = rangeSelectionAux;
		value = valueAux;
		orientation = orientationAux;
		maxValue = maxValueAux;
		minValue = minValueAux;
	};
	~Slider() = default;

	int posX, posY, w, h, rangeSelection, maxValue, minValue;
	float value;
	Orientation orientation;
	SDL_Rect rect;

	void render(SDL_Renderer* renderer) override {

		SDL_SetRenderDrawColor(renderer, 100, 200, 255, 255);

		//Dibujamos su rango
		rect = { posX,posY,w,h };
		SDL_RenderFillRect(renderer, &rect);

		//Y ahora el boton deslizante
		SDL_SetRenderDrawColor(renderer, 200, 100, 150, 255);

		if (orientation == Orientation::HORIZONTAL)
			rect = { posX + ((int)value * w / maxValue),posY,w / rangeSelection,h };
		else
			rect = { posX ,posY + ((int)value * h / maxValue),w,h / rangeSelection };

		SDL_RenderFillRect(renderer, &rect);

	}

	void update(int x, int y, int n_clicks) override {

		// Verificamos si el ratón está dentro de los límites del slider
		if (x >= posX && x < posX + w && y >= posY && y < posY + h) {
			// Calculamos el nuevo valor del slider según la posición del ratón
			float newValue;
			if (orientation == Orientation::HORIZONTAL) {
				newValue = (x - posX) * maxValue / w;
			}
			else {
				newValue = (y - posY) * maxValue / h;
			}

			// Actualizar el valor del slider
			value = newValue;

			// Asegurarse de que el valor esté dentro del rango permitido
			if (value < minValue) {
				value = minValue;
			}
			else if (value > maxValue-(w/rangeSelection)) {
				value = maxValue-(maxValue/rangeSelection);
			}
		}
	}
};

class Toggle : public ianium::Toggle, public HudElement {
public:
	Toggle(const int id, const int posXAux, const int posYAux, const int wAux, const int hAux, const bool active, const char* menu) : ianium::Toggle(id, posX, posY, w, h, active, menu) {
		posX = posXAux;
		posY = posYAux;
		w = wAux;
		h = hAux;
		toogleOn = true;
		buttonPressed = false;
	};
	~Toggle() = default;

	int posX, posY, w, h;
	SDL_Rect rect;
	bool toogleOn, buttonPressed;

	void render(SDL_Renderer* renderer) override {

		//Activao
		if (toogleOn)
			//Verde
			SDL_SetRenderDrawColor(renderer, 0, 220, 10, 255);
		//Desactivado
		else
			//Rojo
			SDL_SetRenderDrawColor(renderer, 220, 0, 10, 255);

		rect = { posX,posY,w,h };
		SDL_RenderFillRect(renderer, &rect);
	}

	void update(int x, int y, int n_clicks) override {

		// Obtener el estado actual del rat�n
		/*int mouseX, mouseY;
		Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);*/

		// Verificar si se ha pulsado el bot�n izquierdo del rat�n
		//if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			// Verificar si el rat�n est� dentro de los l�mites del bot�n
		if (x >= posX && x < posX + w && y >= posY && y < posY + h) {
			// Si el bot�n no estaba presionado previamente
			//if (!buttonPressed) {
				// Cambiar el valor del booleano toogleOn
			for (int i = 0; i < n_clicks; i++)
				toogleOn = !toogleOn;
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

};


int main() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return EXIT_FAILURE;

	SDL_Window* window = SDL_CreateWindow("Juego", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	if (!window)
		return EXIT_FAILURE;

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
		return EXIT_FAILURE;

	ianium::Ianium::Init(window, renderer);

	std::list<HudElement*> hud;

	//Interfaz
	Button* a = new Button(0, 10, 10, 30, 30, true, "u");
	hud.push_back(a);
	Button* b = new Button(1, 60, 0, 60, 60, true, "e");
	hud.push_back(b);
	Button* c = new Button(2, 0, 70, 20, 20, true, "4");
	hud.push_back(c);

	Toggle* t = new Toggle(3, 500, 300, 100, 100, true, "4");
	hud.push_back(t);

	//Falta slider por meter
	Slider* s = new Slider(4, 200, 200, 200, 20, true, "4", 80.0, 0.0, 100.0, 10, ianium::Slider::Orientation::HORIZONTAL);
	hud.push_back(s);

	try
	{
		ianium::Ianium::Instance()->runTests("./scripts");
		// Bucle principal
		bool gameRunning = true;
		while (gameRunning) {
			// Manejar eventos
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					gameRunning = false;
				}
				else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
					gameRunning = false;
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN) {
					//eventos de clickado
					//Update
					for (HudElement* elem : hud)
					{
						elem->update(event.button.x, event.button.y, event.button.clicks);
					}
				}


			}

			// Renderizar elementos
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			//Renderitamos los elementos de la interfaz
			for (HudElement* elem : hud)
			{
				elem->render(renderer);
			}

			//Y lo muestra en pantalla
			SDL_RenderPresent(renderer);

			//insertamos un evento de ianium aqui como testeo

			//ianium::Ianium::Instance()->functionalTesting.click(501, 301);
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl; // output exception message
	}
	ianium::Ianium::Release();

	return 0;
}