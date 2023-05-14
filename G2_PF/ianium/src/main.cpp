#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "ianium/ianium.h"



int WinMain() {
	Ianium::Init();
	Ianium* ia = Ianium::Instance();

	char folderName[] = "laCarpetaDeScripts";
	ia->readFolder(folderName);

	// Bucle principal del entorno
	bool quit = false;
	SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			else if (event.type == SDL_USEREVENT) {

				int y, x,
					element_id;
				switch (event.user.code)
				{
					// Procesa el evento de click
				case 1: {
					//Cogemos los datos necesarios para el evento
					x = reinterpret_cast<int>(event.user.data1);
					y = reinterpret_cast<int>(event.user.data2);

					//Hace cosas

					break;
				}
					//Procesa el evento de doble click
				case 2:

					//Cogemos los datos necesarios para el evento
					x = reinterpret_cast<int>(event.user.data1);
					y = reinterpret_cast<int>(event.user.data2);

					//que hace el evento



					break;
					//Procesa el evento de presionar click
				case 3:


					//Cogemos los datos necesarios para el evento
					x = reinterpret_cast<int>(event.user.data1);
					y = reinterpret_cast<int>(event.user.data2);

					break;
					//Procesa el evento de soltar click
				case 4:

					//tal vez si que necesitamos en que coordenadas se levanta el click

					break;
					//Procesa el evento de click por id
				case 5:


					element_id = reinterpret_cast<int>(event.user.data1);

					//buscar y clickar ese elemento

					break;
				default:
					break;
				}
			}
		}

		//abra que indicarle por aca en que menu/ submenu esta? donde esta el control de eso



		Ianium::Release();
		return 0;
	}
}