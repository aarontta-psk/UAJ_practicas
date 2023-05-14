#include "functional_testing.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <ianium/ianium.h>

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

	// Creamos un evento personalizado
	SDL_Event event;
	event.type = SDL_MOUSEBUTTONDOWN;

	// C�digo personalizado para identificar el evento
	//event.button.button = SDL_BUTTON_LEFT;
	//event.user.code = 1;

	event.button.x = x;
	event.button.y = y;
	event.button.clicks = 1;
	event.button.button = SDL_BUTTON_LEFT;


	//event.user.data1 = reinterpret_cast<void*>(x);  // Datos adicionales (puedes usar data1 y data2)
	//event.user.data2 = reinterpret_cast<void*>(y);

	// Lo pusheamos a la cola de eventos
	SDL_PushEvent(&event);
}

void FunctionalTesting::doubleClick(int x, int y) {

	// Creamos un evento personalizado
	SDL_Event event;
	event.type = SDL_USEREVENT;

	// Primer evento de click
	event.user.code = 1;
	event.user.data1 = reinterpret_cast<void*>(x);
	event.user.data2 = reinterpret_cast<void*>(y);
	SDL_PushEvent(&event);

	// Segundo evento de doble click
	event.user.code = 2;

	//As� enviamos dos eventos de click
	SDL_PushEvent(&event);
}

void FunctionalTesting::pressedClick(int x, int y) {

	// Creamos un evento personalizado
	SDL_Event event;
	event.type = SDL_USEREVENT;

	// C�digo personalizado para clic presionado
	event.user.code = 3;
	event.user.data1 = reinterpret_cast<void*>(x);
	event.user.data2 = reinterpret_cast<void*>(y);

	// Lo pusheamos a la cola de eventos
	SDL_PushEvent(&event);
}

void FunctionalTesting::clickUp() {
	// Creamos un evento personalizado
	SDL_Event event;
	event.type = SDL_USEREVENT;

	// C�digo personalizado para soltar click
	event.user.code = 4;

	event.user.data1 = nullptr;  // No utilizamos data1 en este caso
	event.user.data2 = nullptr;  // No utilizamos data2 en este caso

	// Lo pusheamos a la cola de eventos
	SDL_PushEvent(&event);
}

void FunctionalTesting::click(int id_elem) {

	// Creamos un evento personalizado
	SDL_Event event;
	event.type = SDL_USEREVENT;

	// C�digo personalizado para click por id_elem
	event.user.code = 5;
	event.user.data1 = reinterpret_cast<void*>(id_elem);
	event.user.data2 = nullptr;

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
