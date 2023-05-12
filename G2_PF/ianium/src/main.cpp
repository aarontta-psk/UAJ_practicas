#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "ianium/ianium.h"

int WinMain() {
	Ianium::Init();
	Ianium* ia = Ianium::Instance();

	ia->readFolder("laCarpetaDeScripts");

	Ianium::Release();
	return 0;
}