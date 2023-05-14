#include <ianium/testable_ui/button.h>
#include <ianium/testable_ui/slider.h>
#include <ianium/testable_ui/toggle.h>

#include <ianium/ianium.h>
#include <iostream>
#include <fstream>

#include <list>

class Button : public IAButton {
public:
	Button(int id, int posX, int posY, int w, int h, bool active, const char* menu) : IAButton(id, posX, posY, w, h, active, menu) {};
	~Button() = default;
};

class Slider : public IASlider {
public:
	Slider(const int id, const int posX, const int posY, const int w, const int h, const bool active, const char* menu,
		const float value, const float minValue, const float maxValue, const int rangeSelection, const Orientation orientation)
		:IASlider(id, posX, posY, w, h, active, menu, value, minValue, maxValue, rangeSelection, orientation) {};
	~Slider() = default;
};

class Toogle : public IAToggle {
public:
	Toogle(const int id, const int posX, const int posY, const int w, const int h, const bool active, const char* menu) : IAToggle(id, posX, posY, w, h, active, menu) {};
	~Toogle() = default;
};


int main() {
	Ianium::Init("NOT NEEDED RIGHT NOW CHANGE THIS");

	std::list<UIElement> hud;
	
	//Interfaz
	Button a = Button(0, 0, 0, 0, 0, 0, "u");
	hud.push_back(a);
	Button b = Button(1, 0, 0, 0, 0, 0, "e");
	hud.push_back(b);
	Button c = Button(2, 0, 0, 0, 0, 0, "4");
	hud.push_back(c);
	
	Toogle t = Toogle(3, 10, 10, 10, 10, true, "4");
	hud.push_back(t);
	Slider s = Slider(4, 40, 40, 20, 20, true, "4", 20.0, 0.0, 50.0, 50, IASlider::Orientation::HORIZONTAL);
	hud.push_back(s);


	Ianium::Instance()->visualTesting->testOPENCV("./tempAssets/testImage.jpg");

	try
	{
		//Ianium::Instance()->visualTesting.template_matching("./tempAssets/imageSource.jpg", "./tempAssets/template.jpg");");
		Ianium::Instance()->visualTesting->takeScreenshot();

		// Bucle principal
		bool gameRunning = true;
		while (gameRunning) {
			// Manejar eventos
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					gameRunning = false;
				}
			}

			// Renderizar elementos
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			//Renderitamos los elementos de la interfaz
			for(UIElement elem: hud)
			{

			}

			//Y lo muestra en pantalla
			SDL_RenderPresent(renderer);
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl; // output exception message
	}
	Ianium::Release();

	return 0;
}