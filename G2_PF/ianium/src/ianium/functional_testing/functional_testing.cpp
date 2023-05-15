#include "functional_testing.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <ianium/ianium.h>

using namespace ianium;

void FunctionalTesting::test(const char* path)
{
	std::cout << "Failed to read, " << path << "not found" << std::endl;
}

#pragma region Funciones

//COMO A�ADIR FUNCIONES AL EVENTO//
/*
void myFunction()
{
	// C�digo de la funci�n
}

[Dentro del metodo que sea]
	EventData eventData;
	eventData.functionPointer = &myFunction;

	event.user.data1 = reinterpret_cast<void*>(&eventData);

Esto crea un EventData que tiene un puntero a la funci�n

Para recuperar el puntero en el PollEvents habria que hacer:

  // Recuperamos el puntero a EventData desde data1 o donde este
  EventData* eventData = reinterpret_cast<EventData*>(event.user.data1);

  // Acceder al puntero a funci�n y llamar a la funci�n correspondiente
  if (eventData && eventData->functionPointer)
  {
	  // Llamar a la funci�n
	  eventData->functionPointer();
  }
*/

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

bool FunctionalTesting::IsElemOnMenu(int id_elem) {

	Ianium::Instance()->searchActiveUIElement(id_elem);
	return false;
}

bool FunctionalTesting::Assert() {

	return false;
}

#pragma endregion
