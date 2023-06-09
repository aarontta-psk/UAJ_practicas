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

	if (!ianium::Ianium::Init(window, renderer))
		return EXIT_FAILURE;

	//Interfaz
	std::list<HudElement*> hud;

	hud.push_back(new Button(renderer, "./assets/mainmenu.png", "./assets/mainmenu.png", 3, 300, 50, 200, 100, true));
	hud.push_back(new Button(renderer, "./assets/buttonPressed.png", "./assets/buttonReleased.png", 0, 100, 150, 100, 50, true));
	hud.push_back(new Button(renderer, "./assets/buttonPressed.png", "./assets/buttonReleased.png", 1, 100, 210, 100, 50, true));
	hud.push_back(new Button(renderer, "./assets/buttonPressed.png", "./assets/buttonReleased.png", 2, 100, 270, 100, 50, true));

	hud.push_back(new Toggle(renderer, "./assets/toggleOn.png", "./assets/toggleOff.png", 4, 100, 320, 100, 100, true));
	hud.push_back(new Slider(renderer, "./assets/sliderRange.png", "./assets/sliderButton.png", 5, 100, 450, 200, 20, true, 0.8, 0.0, 100.0, Slider::Orientation::HORIZONTAL));

	hud.push_back(new WrongButton(renderer, "./assets/buttonPressed.png", "./assets/buttonReleased.png", 6, 500, 150, 100, 50, true));
	hud.push_back(new WrongButton(renderer, "./assets/buttonPressed.png", "./assets/buttonReleased.png", 7, 500, 210, 100, 50, true));
	hud.push_back(new WrongButton(renderer, "./assets/buttonPressed.png", "./assets/buttonReleased.png", 8, 500, 270, 100, 50, true));

	hud.push_back(new WrongToggle(renderer, "./assets/toggleOn.png", "./assets/toggleOff.png", 9, 500, 320, 100, 100, true));
	hud.push_back(new WrongSlider(renderer, "./assets/sliderRange.png", "./assets/sliderButton.png", 10, 500, 450, 200, 20, true, 0.8, 0.0, 100.0, WrongSlider::Orientation::HORIZONTAL));
	
	try
	{
		// test running
		ianium::Ianium::Instance()->runTests("./scripts");

		// game loop
		bool gameRunning = true;
		while (gameRunning) {
			// Manejar eventos
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
					gameRunning = false;
				else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
					// handle input
					for (HudElement* elem : hud)
						elem->handleInput(event);
			}

			// render clear
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			// render elements
			for (HudElement* elem : hud)
				elem->render(renderer);

			// render present
			SDL_RenderPresent(renderer);
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl; // output exception message
	}
	
	// delete ui elements
	for (HudElement* elem : hud)
		delete elem;
	hud.clear();

	// release Ianium
	ianium::Ianium::Release();

	// delete SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window); 
	SDL_Quit();

	return 0;
}