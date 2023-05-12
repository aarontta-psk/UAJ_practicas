#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "ianium/ianium.h"

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

void click(int x, int y) {

	// Creamos un evento personalizado
	SDL_Event event;
	event.type = SDL_USEREVENT;

	// C�digo personalizado para identificar el evento
	event.user.code = 1;
	event.user.data1 = reinterpret_cast<void*>(x);  // Datos adicionales (puedes usar data1 y data2)
	event.user.data2 = reinterpret_cast<void*>(y);

	// Lo pusheamos a la cola de eventos
	SDL_PushEvent(&event);
}

void doubleClick(int x, int y) {

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

void pressedClick(int x, int y) {

	// Creamos un evento personalizado
	SDL_Event event;
	event.type = SDL_USEREVENT;

	// C�digo personalizado para clic presionado
	event.user.code = 3;

	// Lo pusheamos a la cola de eventos
	SDL_PushEvent(&event);
}

void clickUp() {
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

void click(int id_elem) {

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
#pragma endregion

int WinMain() {
	Ianium::Init();
	Ianium* ia = Ianium::Instance();

	ia->readFolder("laCarpetaDeScripts");

	// Bucle principal del entorno
	bool quit = false;
	SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			else if (event.type == SDL_USEREVENT) {

				switch (event.user.code)
				{
					// Procesa el evento de click
				case 1: {
					//Cogemos los datos necesarios para el evento
					int x = reinterpret_cast<int>(event.user.data1);
					int y = reinterpret_cast<int>(event.user.data2);

					//Hace cosas

					break;
				}
					//Procesa el evento de doble click
				case 2:
					break;
					//Procesa el evento de presionar click
				case 3:
					break;
					//Procesa el evento de soltar click
				case 4:
					break;
					//Procesa el evento de click por id
				case 5:
					break;
				default:
					break;
				}
			}
		}

		Ianium::Release();
		return 0;
	}
}