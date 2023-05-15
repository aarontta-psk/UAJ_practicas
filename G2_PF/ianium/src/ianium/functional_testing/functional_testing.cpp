#include "functional_testing.h"

#include <iostream>
#include <string>

#include <SDL2/SDL.h>

#include <ianium/ianium.h>
#include <ianium/testable_ui/ui_element.h>
#include <ianium/testable_ui/button.h>

using namespace ianium;

FunctionalTesting::FunctionalTesting(std::unordered_map<std::string, UIElement*>* uiTestElems, SDL_Renderer* sdl_renderer) {
	uiElems = uiTestElems;
	renderer = sdl_renderer;
}

FunctionalTesting::~FunctionalTesting() = default;

#pragma region Funciones
void FunctionalTesting::click(int id_elem) {

	SDL_Event event;
	event.type = SDL_MOUSEBUTTONDOWN;
	event.button.x = 0;// x;
	event.button.y = 0;// y;
	event.button.clicks = 1;
	event.button.button = SDL_BUTTON_LEFT;


	// Lo pusheamos a la cola de eventos
	SDL_PushEvent(&event);
}

void FunctionalTesting::click(int x, int y) {

	SDL_Event event;
	event.type = SDL_MOUSEBUTTONDOWN;
	event.button.x = x;
	event.button.y = y;
	event.button.clicks = 1;
	event.button.button = SDL_BUTTON_LEFT;


	// Lo pusheamos a la cola de eventos
	SDL_PushEvent(&event);
}

void FunctionalTesting::clickUp(int x, int y) {
	SDL_Event event;
	event.type = SDL_MOUSEBUTTONUP;
	event.button.x = x;
	event.button.y = y;
	event.button.clicks = 1;
	event.button.state = SDL_RELEASED;

	event.button.button = SDL_BUTTON_LEFT;


	// Lo pusheamos a la cola de eventos
	SDL_PushEvent(&event);
}

void FunctionalTesting::doubleClick(int x, int y) {

	SDL_Event event;
	event.type = SDL_MOUSEBUTTONDOWN;
	event.button.x = x;
	event.button.y = y;
	event.button.clicks = 2;
	event.button.button = SDL_BUTTON_LEFT;


	// Lo pusheamos a la cola de eventos
	SDL_PushEvent(&event);
}

void FunctionalTesting::pressedClick(int x, int y) {

	SDL_Event event;
	event.type = SDL_MOUSEBUTTONDOWN;
	event.button.x = x;
	event.button.y = y;
	event.button.clicks = 0;
	event.button.state = SDL_PRESSED;
	event.button.button = SDL_BUTTON_LEFT;


	// Lo pusheamos a la cola de eventos
	SDL_PushEvent(&event);
}

void FunctionalTesting::mouseMotion(int x, int y)
{
	SDL_Event event;
	event.type = SDL_MOUSEMOTION;
	event.button.x = x;
	event.button.y = y;
	//event.button.clicks = 1;
	//event.button.button = SDL_BUTTON_LEFT;


	// Lo pusheamos a la cola de eventos
	SDL_PushEvent(&event);
}

bool FunctionalTesting::isElemOnMenu(int id_elem) {

	return false;
}

bool FunctionalTesting::assertButton(std::string idButton, int stateToCheck) {
	auto elem = uiElems->find(idButton);
	if (elem != uiElems->end()) {
		Button::State state = ((Button*)elem->second)->getStateButton();
		return (int)state == stateToCheck;
	}
	std::cerr << "Button " << idButton << " not found";
	return false;
}

void FunctionalTesting::run(uint32_t n_frames) {
	while (!n_frames) {
		// handle input
		SDL_Event i_event;
		while (SDL_PollEvent(&i_event))
			for (std::pair<std::string, UIElement*> elem : (*uiElems))
				elem.second->handleInput(i_event);
		
		// render
		SDL_RenderClear(renderer);
		for (std::pair<std::string, UIElement*> elem : (*uiElems))
			elem.second->handleInput(i_event);
		SDL_RenderPresent(renderer);

		n_frames--;
	}
}
#pragma endregion

std::string FunctionalTesting::elemPrefix(UIType uiType) {
	switch (uiType)
	{
	case UIType::BUTTON:
		return "button_";
		break;
	case UIType::TOGGLE:
		return "toggle_";
		break;
	case UIType::SLIDER:
		return "slider_";
		break;
	default:
		return "";
		break;
	}
}