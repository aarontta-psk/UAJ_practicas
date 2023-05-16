#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

//#include <ianium/testable_ui/button.h>
//#include <ianium/testable_ui/slider.h>
//#include <ianium/testable_ui/toggle.h>
//
//#include <ianium/ianium.h>
#include <iostream>
#include <fstream>

#include <list>

/*UiElements*/
#include "Button.h"
#include "Slider.h"
#include "Toggle.h"


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
	hud.push_back(new Button("./buttonPressed.png", "./buttonReleased.png", 0, 350, 150, 100, 50, true, renderer));
	hud.push_back(new Button("./buttonPressed.png", "./buttonReleased.png", 1, 350, 200, 100, 50, true, renderer));
	hud.push_back(new Button("./buttonPressed.png", "./buttonReleased.png", 1, 350, 250, 100, 50, true, renderer));
	hud.push_back(new Button("./mainmenu.png", "./mainmenu.png", 2, 300, 20, 200, 100, true, renderer));

	hud.push_back(new Toggle("./toggleOn.png", "./toggleOff.png", 3, 500, 300, 100, 100, true, renderer));
	hud.push_back(new Slider("./sliderRange.png", "./sliderButton.png", 4, 200, 200, 200, 20, true, 80.0, 0.0, 100.0, 10, Slider::Orientation::HORIZONTAL, renderer));


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
				else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
					//eventos de clickado
					//Update
					for (HudElement* elem : hud)
					{
						elem->handleInput(event);
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
	
	for (HudElement* elem : hud)
		delete elem;
	hud.clear();

	ianium::Ianium::Release();

	return 0;
}