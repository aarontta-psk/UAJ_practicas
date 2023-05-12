#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "ianium/ianium.h"


void click(int x, int y) {

    // Creamos un evento personalizado
    SDL_Event event;
    event.type = SDL_USEREVENT;  

    // Código personalizado para identificar el evento
    event.user.code = 1;  
    event.user.data1 = reinterpret_cast<void*>(x);  // Datos adicionales (puedes usar data1 y data2)
    event.user.data2 = reinterpret_cast<void*>(y);

    SDL_PushEvent(&event);  // Agregar el evento a la cola de eventos
}

void DoubleClick(int x, int y) {

    // Creamos un evento personalizado
    SDL_Event event;
    event.type = SDL_USEREVENT;

    // Primer evento de clic
    event.user.code = 1;
    event.user.data1 = reinterpret_cast<void*>(x);
    event.user.data2 = reinterpret_cast<void*>(y);
    SDL_PushEvent(&event);

    // Segundo evento de clic
    event.user.code = 2;
    SDL_PushEvent(&event);
}

void PressedClick(int x, int y) {

    // Creamos un evento personalizado
    SDL_Event event;
    event.type = SDL_USEREVENT;

    // Código personalizado para clic presionado
    event.user.code = 3;

    event.user.data1 = reinterpret_cast<void*>(x);
    event.user.data2 = reinterpret_cast<void*>(y);
    SDL_PushEvent(&event);
}


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
                if (event.user.code == 1) {
                    int x = reinterpret_cast<int>(event.user.data1);
                    int y = reinterpret_cast<int>(event.user.data2);

                    // Procesar el evento de clic personalizado
                    // Aquí puedes llamar a las funciones que prueban tu UI del juego
                }
            }
        }



	Ianium::Release();
	return 0;
}