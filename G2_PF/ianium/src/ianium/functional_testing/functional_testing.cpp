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
	// clicks in the middle of the element
	std::string ui_elem_id = elemPrefix(uiType) + std::to_string(id_elem);

	auto got = uiElems->find(ui_elem_id);
	std::pair<uint32_t, uint32_t> pos = got->second->getPosition();
	std::pair<uint32_t, uint32_t> size = got->second->getSize();

	int x, y;
	x = pos.first + (size.first / 2);
	y = pos.second + (size.second / 2);

	SDL_Event i_event;
	i_event.type = SDL_MOUSEBUTTONDOWN;
	i_event.button.x = x;
	i_event.button.y = y;
	i_event.button.clicks = 1;
	i_event.button.button = SDL_BUTTON_LEFT;
	i_event.button.state = SDL_PRESSED;
	SDL_PushEvent(&i_event);
}

void FunctionalTesting::click(uint32_t x, uint32_t y) {
	SDL_Event i_event;
	i_event.type = SDL_MOUSEBUTTONDOWN;
	i_event.button.x = x;
	i_event.button.y = y;
	i_event.button.clicks = 1;
	i_event.button.button = SDL_BUTTON_LEFT;
	i_event.button.state = SDL_PRESSED;
	SDL_PushEvent(&i_event);
}

void FunctionalTesting::releaseClick(uint32_t x, uint32_t y) {
	SDL_Event i_event;
	i_event.type = SDL_MOUSEBUTTONUP;
	i_event.button.x = x;
	i_event.button.y = y;
	i_event.button.clicks = 1;
	i_event.button.state = SDL_RELEASED;
	i_event.button.button = SDL_BUTTON_LEFT;
	SDL_PushEvent(&i_event);
}

void FunctionalTesting::doubleClick(uint32_t x, uint32_t y) {
	SDL_Event i_event;
	i_event.type = SDL_MOUSEBUTTONDOWN;
	i_event.button.x = x;
	i_event.button.y = y;
	i_event.button.clicks = 2;
	i_event.button.button = SDL_BUTTON_LEFT;
	SDL_PushEvent(&i_event);
}

void FunctionalTesting::pressedClick(uint32_t x, uint32_t y) {
	SDL_Event i_event;
	i_event.type = SDL_MOUSEBUTTONDOWN;
	i_event.button.x = x;
	i_event.button.y = y;
	i_event.button.clicks = 0;
	i_event.button.state = SDL_PRESSED;
	i_event.button.button = SDL_BUTTON_LEFT;
	SDL_PushEvent(&i_event);
}

void FunctionalTesting::mouseMotion(uint32_t x, uint32_t y) {
	SDL_Event event;
	event.type = SDL_MOUSEMOTION;
	event.button.x = x;
	event.button.y = y;
	SDL_PushEvent(&event);
}

bool FunctionalTesting::assertButton(uint64_t idButton, uint32_t stateToCheck) {
	auto elem = uiElems->find(elemPrefix(UIType::BUTTON) + std::to_string(idButton));
	if (elem != uiElems->end()) {
		uint32_t state = ((Button*)elem->second)->getStateButton();
		return state == stateToCheck;
	}
	std::cerr << "Button " << idButton << " not found" << std::endl;
	return false;
}

bool ianium::FunctionalTesting::assertToggle(uint64_t idToggle, uint32_t stateToCheck) {
	auto elem = uiElems->find(elemPrefix(UIType::TOGGLE) + std::to_string(idToggle));
	if (elem != uiElems->end()) {
		bool state = ((Toggle*)elem->second)->getToggleState();
		return state == stateToCheck;
	}
	std::cerr << "Toggle " << idToggle << " not found" << std::endl;
	return false;
}

bool ianium::FunctionalTesting::assertSlider(uint64_t idSlider, float value) {
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