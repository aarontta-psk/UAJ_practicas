#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <ianium/testable_ui/button.h>
#include <ianium/testable_ui/slider.h>
#include <ianium/testable_ui/toggle.h>

#include <ianium/ianium.h>
#include <iostream>
#include <fstream>

#include <list>

class Button : public IAButton {
public:
	Button(int id, int posXAux, int posYAux, int wAux, int hAux, bool active, const char* menu) : IAButton(id, posX, posY, w, h, active, menu) {
		posX = posXAux;
		posY = posYAux;
		w = wAux;
		h = hAux;
	};
	~Button() = default;

	int posX, posY, w, h;

	SDL_Rect rect;

	void render(SDL_Renderer* renderer) {

		//Cuadrado rosita
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

		rect = { posX,posY,w,h };
		SDL_RenderFillRect(renderer, &rect);
	}
};

class Slider : public IASlider {
public:
	Slider(const int id, const int posXAux, const int posYAux, const int wAux, const int hAux, const bool active, const char* menu,
		const float value, const float minValue, const float maxValue, const int rangeSelection, const Orientation orientation)
		:IASlider(id, posX, posY, w, h, active, menu, value, minValue, maxValue, rangeSelection, orientation) {
		posX = posXAux;
		posY = posYAux;
		w = wAux;
		h = hAux;
	};
	~Slider() = default;

	int posX, posY, w, h;
	Orientation orientation;
	SDL_Rect rect;

	void render(SDL_Renderer* renderer) {

		SDL_SetRenderDrawColor(renderer, 100, 200, 255, 255);

		if (orientation == Orientation::VERTICAL) {

		}
		else {


		}


		rect = { posX,posY,w,h };
		SDL_RenderFillRect(renderer, &rect);
	}
};

class Toggle : public IAToggle {
public:
	Toggle(const int id, const int posXAux, const int posYAux, const int wAux, const int hAux, const bool active, const char* menu) : IAToggle(id, posX, posY, w, h, active, menu) {
		posX = posXAux;
		posY = posYAux;
		w = wAux;
		h = hAux;
		toogleOn = true;
	};
	~Toggle() = default;

	int posX, posY, w, h;
	SDL_Rect rect;
	bool toogleOn;

	void render(SDL_Renderer* renderer) {

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
};


int main() {

	// Inicializar SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Creamos la ventana
	SDL_Window* window = SDL_CreateWindow("Juego", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

	// Creamos un renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	Ianium::Init("NOT NEEDED RIGHT NOW CHANGE THIS");

	std::list<Toggle> hud;

	//Interfaz
	//Button a = Button(0, 10, 10, 30, 30, true, "u");
	//hud.push_back(a);
	//Button b = Button(1, 60, 0, 60, 60, true, "e");
	//hud.push_back(b);
	//Button c = Button(2, 0, 70, 20, 20, true, "4");
	//hud.push_back(c);

	Toggle t = Toggle(3, 500,300,100,100, true, "4");
	hud.push_back(t);
	//Slider s = Slider(4, 40, 40, 20, 20, true, "4", 20.0, 0.0, 50.0, 50, IASlider::Orientation::HORIZONTAL);
	//hud.push_back(s);

	Ianium::Instance()->visualTesting->testOPENCV("./tempAssets/testImage.jpg");

	try
	{
		//Ianium::Instance()->visualTesting.template_matching("./tempAssets/imageSource.jpg", "./tempAssets/template.jpg");");
		Ianium::Instance()->visualTesting->takeScreenshot();

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
			}

			// Renderizar elementos
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			//Renderitamos los elementos de la interfaz
			for (Toggle elem : hud)
			{
				elem.render(renderer);
			}

			//Y lo muestra en pantalla
			SDL_RenderPresent(renderer);
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl; // output exception message
	}
	Ianium::Release();

	return 0;
}