#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <ianium/testable_ui/button.h>
#include <ianium/testable_ui/slider.h>
#include <ianium/testable_ui/toggle.h>

#include <ianium/ianium.h>
#include <iostream>
#include <fstream>

#include <list>

#define CONVERT_RGBA_TO_ARGB(value) ((value & 0xFF000000) >> 8) | ((value & 0x00FF0000) >> 8) | ((value & 0x0000FF00) >> 8) | ((value & 0x000000FF) << 24)
#define CONVERT_ENDIANESS_32(value) ((value & 0xFF000000) >> 24) | ((value & 0x00FF0000) >> 8) | ((value & 0x0000FF00) << 8) | ((value & 0x000000FF) << 24)


class HudElement {
public:
	HudElement() {};
	~HudElement() = default;

	virtual void render(SDL_Renderer* renderer) {}
	virtual void update(int x, int y, int n_clicks) {}
	virtual void processInput(SDL_Event* event) {}

};
class Image {
public:
	Image(std::string path, SDL_Renderer* renderer) {
		surface = IMG_Load(path.c_str());
		if (!surface) {
			// Error
			std::cout << "Failure loading image " << path << ": " << IMG_GetError() << std::endl;
			return;
		}

		// Crear una textura a partir de la superficie
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		if (!texture) {
			// Manejar error de creación de textura
			std::cout << "Failure creating texture: " << SDL_GetError() << std::endl;
			SDL_FreeSurface(surface);
			return;
		}

		// Obtener el ancho y alto de la imagen
		w = surface->w;
		h = surface->h;

	}

	~Image() {
		SDL_FreeSurface(surface);
		surface = nullptr;

		SDL_DestroyTexture(texture);
		texture = nullptr;

	}

	void render(SDL_Rect rect, SDL_Renderer* renderer) {
		if (texture) {
			SDL_RenderCopy(renderer, texture, nullptr, &rect);
		}
		else {
			// Cuadrado rosita
			SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
			SDL_RenderFillRect(renderer, &rect);
		}
	}

private:
	uint32_t w, h;
	SDL_Texture* texture;
	SDL_Surface* surface;
};

class Button : public ianium::Button, public HudElement {
public:
	Button(std::string path, int id, int posXAux, int posYAux, int wAux, int hAux, bool active, const char* menu, SDL_Renderer* renderer) : ianium::Button(id, posX, posY, w, h, active, menu) {
		posX = posXAux;
		posY = posYAux;
		w = wAux;
		h = hAux;

		image = new Image(path, renderer);
	};
	~Button() {
		delete image;
	};

	int posX, posY, w, h;

	SDL_Rect rect;
	Image* image;

	virtual void render(SDL_Renderer* renderer) override {

		rect = { posX,posY,w,h };

		image->render(rect, renderer);
	}

	virtual void handleInput(const SDL_Event& i_event) {};
};

class Slider : public ianium::Slider, public HudElement {
public:
	Slider(std::string pathRange, std::string pathValue, const int id, const int posXAux, const int posYAux, const int wAux, const int hAux, const bool active, const char* menu,
		const float valueAux, const float minValueAux, const float maxValueAux, const int rangeSelectionAux, const Orientation orientationAux, SDL_Renderer* renderer)
		: ianium::Slider(id, posX, posY, w, h, active, menu, valueAux, minValueAux, maxValueAux, rangeSelectionAux, orientationAux) {
		posX = posXAux;
		posY = posYAux;
		w = wAux;
		h = hAux;
		rangeSelection = rangeSelectionAux;
		value = valueAux;
		orientation = orientationAux;
		maxValue = maxValueAux;
		minValue = minValueAux;

		imageRange = new Image(pathRange, renderer);
		imageValue = new Image(pathValue, renderer);
	};
	~Slider() = default;

	int posX, posY, w, h, rangeSelection, maxValue, minValue;
	float value;
	Orientation orientation;
	SDL_Rect rect;
	Image* imageRange;
	Image* imageValue;

	virtual void render(SDL_Renderer* renderer) override {

		//Dibujamos su rango
		rect = { posX,posY,w,h };

		imageRange->render(rect, renderer);

		//Y ahora el boton deslizante
		if (orientation == Orientation::HORIZONTAL)
			rect = { posX + ((int)value * w / maxValue),posY,w / rangeSelection,h };
		else
			rect = { posX ,posY + ((int)value * h / maxValue),w,h / rangeSelection };

		imageValue->render(rect, renderer);
	}

	void update(int x, int y, int n_clicks) override {

		// Verificamos si el ratón está dentro de los límites del slider
		if (x >= posX && x < posX + w && y >= posY && y < posY + h) {
			// Calculamos el nuevo valor del slider según la posición del ratón
			float newValue;
			if (orientation == Orientation::HORIZONTAL) {
				newValue = (x - posX) * maxValue / w;
			}
			else {
				newValue = (y - posY) * maxValue / h;
			}

			// Actualizar el valor del slider
			value = newValue;

			// Asegurarse de que el valor esté dentro del rango permitido
			if (value < minValue) {
				value = minValue;
			}
			else if (value > maxValue - (w / rangeSelection)) {
				value = maxValue - (maxValue / rangeSelection);
			}
		}
	}

	virtual void handleInput(const SDL_Event& i_event) {};
};

class Toggle : public ianium::Toggle, public HudElement {
public:
	Toggle(std::string pathToogleOn, std::string pathToogleOff, const int id, const int posXAux, const int posYAux, const int wAux, const int hAux, const bool active, const char* menu, SDL_Renderer* renderer) : ianium::Toggle(id, posX, posY, w, h, active, menu) {
		posX = posXAux;
		posY = posYAux;
		w = wAux;
		h = hAux;
		toogleOn = true;
		buttonPressed = false;
		imageOn = new Image(pathToogleOn, renderer);
		imageOff = new Image(pathToogleOff, renderer);

	};
	~Toggle() = default;

	int posX, posY, w, h;
	SDL_Rect rect;
	bool toogleOn, buttonPressed;
	Image* imageOn;
	Image* imageOff;

	virtual void render(SDL_Renderer* renderer) override {
		rect = { posX,posY,w,h };

		//Activao
		if (toogleOn)
			imageOn->render(rect, renderer);

		//Desactivado
		else
			imageOff->render(rect, renderer);
	}

	void update(int x, int y, int n_clicks) override {

		// Obtener el estado actual del rat�n
		/*int mouseX, mouseY;
		Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);*/

		// Verificar si se ha pulsado el bot�n izquierdo del rat�n
		//if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			// Verificar si el rat�n est� dentro de los l�mites del bot�n
		if (x >= posX && x < posX + w && y >= posY && y < posY + h) {
			// Si el bot�n no estaba presionado previamente
			//if (!buttonPressed) {
				// Cambiar el valor del booleano toogleOn
			for (int i = 0; i < n_clicks; i++)
				toogleOn = !toogleOn;
			// Establecer el estado de bot�n como presionado
			//buttonPressed = true;
		//}
		}
		//}
		//else {
		//	// Si se ha soltado el bot�n, establecer el estado de bot�n como no presionado
		//	buttonPressed = false;
		//}
	}
	virtual void handleInput(const SDL_Event& i_event) {};
};


int main() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return EXIT_FAILURE;

	SDL_Window* window = SDL_CreateWindow("Juego", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	if (!window)
		return EXIT_FAILURE;

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
		return EXIT_FAILURE;

	ianium::Ianium::Init(window, renderer);

	std::list<HudElement*> hud;
	SDL_Surface* image = IMG_Load("testImage.jpg");
	//Interfaz
	Button* a = new Button("./button.png", 0, 10, 10, 30, 30, true, "InterfazSimple", renderer);
	hud.push_back(a);
	Button* b = new Button("./button.png",1, 60, 0, 60, 60, true, "InterfazSimple", renderer);
	hud.push_back(b);
	Button* c = new Button("./tempAssets/template.jpg",2, 0, 300, 355, 255, true, "InterfazSimple", renderer);
	hud.push_back(c);

	Toggle* t = new Toggle("./toggleOn.png", "./toggleOff.png", 3, 500, 300, 100, 100, true, "InterfazCompleja", renderer);
	hud.push_back(t);

	//Falta slider por meter
	Slider* s = new Slider("./sliderRange.png", "./sliderButton.png", 4, 200, 200, 200, 20, true, "InterfazCompleja", 80.0, 0.0, 100.0, 10, ianium::Slider::Orientation::HORIZONTAL, renderer);
	hud.push_back(s);

	try
	{
		ianium::Ianium::Instance()->runTests("./scripts");
		// Bucle principal
		bool gameRunning = true;
		while (gameRunning) {
			// Manejar eventos
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					gameRunning = false;
				}
				else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
					gameRunning = false;
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN) {
					//eventos de clickado
					//Update
					for (HudElement* elem : hud)
					{
						elem->update(event.button.x, event.button.y, event.button.clicks);
					}
				}


			}

			// Renderizar elementos
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			//Renderitamos los elementos de la interfaz
			for (HudElement* elem : hud)
			{
				elem->render(renderer);
			}

			//Y lo muestra en pantalla
			SDL_RenderPresent(renderer);

			//insertamos un evento de ianium aqui como testeo

			//ianium::Ianium::Instance()->functionalTesting.click(501, 301);
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl; // output exception message
	}
	ianium::Ianium::Release();

	return 0;
}