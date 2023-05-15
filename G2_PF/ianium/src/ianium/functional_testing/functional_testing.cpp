#include "functional_testing.h"

#include <iostream>
#include <string>

#include <SDL2/SDL.h>

#include <ianium/ianium.h>
#include <ianium/testable_ui/ui_element.h>
#include <ianium/testable_ui/button.h>
#include <ianium/testable_ui/toggle.h>
#include <ianium/testable_ui/slider.h>

using namespace ianium;

FunctionalTesting::FunctionalTesting(std::unordered_map<std::string, UIElement*>* uiTestElems, SDL_Renderer* sdl_renderer) {
	uiElems = uiTestElems;
	renderer = sdl_renderer;
}

FunctionalTesting::~FunctionalTesting() = default;

#pragma region Funciones
void FunctionalTesting::click(UIType uiType, uint64_t id_elem) {

	SDL_Event event;
	event.type = SDL_MOUSEBUTTONDOWN;

	/*clicar en medio del elemento de ui*/
	std::string ui_elem_id = elemPrefix(uiType) + std::to_string(id_elem);

	auto got = uiElems->find(ui_elem_id);

	std::pair<uint32_t, uint32_t> pos = got->second->getPosition();
	std::pair<uint32_t, uint32_t> size = got->second->getSize();

	int x, y;

	x = pos.first + (size.first / 2);
	y = pos.second + (size.second / 2);
	/*calculo terminado aplicar los datos el evento de sdl*/

	event.button.x = x;
	event.button.y = y;
	event.button.clicks = 1;
	event.button.button = SDL_BUTTON_LEFT;
	event.button.state = SDL_PRESSED;

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
	event.button.state = SDL_PRESSED;


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

bool FunctionalTesting::assertButton(int idButton, int stateToCheck) {
	auto elem = uiElems->find(elemPrefix(UIType::BUTTON) + std::to_string(idButton));
	if (elem != uiElems->end()) {
		uint32_t state = ((Button*)elem->second)->getStateButton();
		return state == stateToCheck;
	}
	std::cerr << "Button " << idButton << " not found" << std::endl;
	return false;
}

bool ianium::FunctionalTesting::assertToggle(int idToggle, int stateToCheck)
{
	auto elem = uiElems->find(elemPrefix(UIType::TOGGLE) + std::to_string(idToggle));
	if (elem != uiElems->end()) {
		bool state = ((Toggle*)elem->second)->getToggleState();
		return state == stateToCheck;
	}
	std::cerr << "Toggle " << idToggle << " not found" << std::endl;
	return false;
}

bool ianium::FunctionalTesting::assertSlider(int idSlider, float value)
{
	auto elem = uiElems->find(elemPrefix(UIType::SLIDER) + std::to_string(idSlider));
	if (elem != uiElems->end()) {
		float state = ((Slider*)elem->second)->getValue();
		return (std::abs(state - value) < 0.01f);
	}
	std::cerr << "Slider " << idSlider << " not found" << std::endl;
	return false;
}

void FunctionalTesting::runFrames(uint32_t n_frames) {
	while (n_frames) {
		// handle input
		SDL_Event i_event;
		while (SDL_PollEvent(&i_event))
			for (std::pair<std::string, UIElement*> elem : (*uiElems))
				elem.second->handleInput(i_event);
		
		// render
		SDL_RenderClear(renderer);
		for (std::pair<std::string, UIElement*> elem : (*uiElems))
			elem.second->render(renderer);
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