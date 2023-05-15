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

class HudElement {
public:
	HudElement(int posXAux, int posYAux, int widthAux, int heightAux, bool isActiveAux) :posX(posXAux), posY(posYAux), width(widthAux), height(heightAux), isActive(isActiveAux) {};
	~HudElement() = default;

	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void handleInput(const SDL_Event& event) {};

protected:
	uint32_t posX, posY;    // Posición X e Y del elemento
	uint32_t width, height; // Ancho y alto del elemento                
	bool isActive;          // Estado del elemento (Activado o desactivado)         
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
	enum class State { PRESSED, HOLD, RELEASED };

	Button(std::string path, int id, int posXAux, int posYAux, int wAux, int hAux, bool active, SDL_Renderer* renderer) : ianium::Button(id), HudElement(posXAux, posYAux, wAux, hAux, active) {
		buttonState = State::RELEASED;
		image = new Image(path, renderer);
	};
	~Button() {
		delete image;
	};

	//REDEFINICIONES CLASE UUIELEMENT
	// Devuelve la posición (X, Y) del elemento
	virtual std::pair<uint32_t, uint32_t> getPosition() const { return std::make_pair(posX, posY); };
	// Devuelve el tamaño (ancho, alto) del elemento
	virtual std::pair<uint32_t, uint32_t> getSize() const { return std::make_pair(width, height); };
	// Devuelve el estado del elemento
	virtual bool getEnable() const { return isActive; }

	//REDEFINICIONES CLASE BUTTON
	virtual int getStateButton() const { return (int)buttonState; }


	virtual void render(SDL_Renderer* renderer) override {

		rect = { (int)posX,(int)posY,(int)width,(int)height };

		image->render(rect, renderer);
	}

	//TODO AAA METER AQUI QUE EL ESTADO DEL BOTON SEA PRESSED HOLD O RELEASED
	virtual void handleInput(const SDL_Event& i_event) {};
private:
	//TODO FALTA ESTE ESTADO DE KK
	State buttonState;

	SDL_Rect rect;
	Image* image;
};

class Slider : public ianium::Slider, public HudElement {
public:
	enum class Orientation { VERTICAL, HORIZONTAL };

	Slider(std::string pathRange, std::string pathValue, const int id, const int posXAux, const int posYAux, const int wAux, const int hAux, const bool active,
		const float valueAux, const float minValueAux, const float maxValueAux, const int rangeSelectionAux, const Orientation orientationAux, SDL_Renderer* renderer)
		: ianium::Slider(id), HudElement(posXAux, posYAux, wAux, hAux, active) {

		value = valueAux;
		minValue = minValueAux;
		maxValue = maxValueAux;
		rangeSelection = rangeSelectionAux;
		orientation = orientationAux;

		imageRange = new Image(pathRange, renderer);
		imageValue = new Image(pathValue, renderer);
	};
	~Slider() = default;

	//REDEFINICIONES CLASE UIELEMENT
	// Devuelve la posición (X, Y) del elemento
	virtual std::pair<uint32_t, uint32_t> getPosition() const { return std::make_pair(posX, posY); };
	// Devuelve el tamaño (ancho, alto) del elemento
	virtual std::pair<uint32_t, uint32_t> getSize() const { return std::make_pair(width, height); };
	// Devuelve el estado del elemento
	virtual bool getEnable() const { return isActive; }

	//REDEFINICIONES CLASE SLIDER
	virtual float getValue() const { return value; }
	virtual float getMinValue() const { return minValue; }
	virtual float getMaxValue() const { return maxValue; }
	virtual int getRangeSelection() const { return rangeSelection; }

	virtual void render(SDL_Renderer* renderer) override {

		//Dibujamos su rango
		rect = { (int)posX,(int)posY,(int)width,(int)height };

		imageRange->render(rect, renderer);

		//Y ahora el boton deslizante
		if (orientation == Orientation::HORIZONTAL)
			rect = { (int)posX + ((int)value * (int)width / (int)maxValue),(int)posY,(int)width / rangeSelection,(int)height };
		else
			rect = { (int)posX ,(int)posY + ((int)value * (int)height / (int)maxValue),(int)width,(int)height / rangeSelection };

		imageValue->render(rect, renderer);
	}



	virtual void handleInput(const SDL_Event& i_event) {
		int x = i_event.button.x;
		int y = i_event.button.y;

		// Verificamos si el ratón está dentro de los límites del slider
		if (x >= posX && x < posX + width && y >= posY && y < posY + height) {
			// Calculamos el nuevo valor del slider según la posición del ratón
			float newValue;
			if (orientation == Orientation::HORIZONTAL) {
				newValue = (x - posX) * maxValue / width;
			}
			else {
				newValue = (y - posY) * maxValue / height;
			}

			// Actualizar el valor del slider
			value = newValue;

			// Asegurarse de que el valor esté dentro del rango permitido
			if (value < minValue) {
				value = minValue;
			}
			else if (value > maxValue - (width / rangeSelection)) {
				value = maxValue - (maxValue / rangeSelection);
			}
		}
	};

private:
	float value;					// Valor actual del slider
	float minValue, maxValue;		// Valor mínimo y maximo del slider
	int rangeSelection;				// Cantidad de valores que se pueden seleccionar en el slider      
	Orientation orientation;		// Orientación del slider (horizontal o vertical)

	SDL_Rect rect;
	Image* imageRange;
	Image* imageValue;

};

class Toggle : public ianium::Toggle, public HudElement {
public:
	Toggle(std::string pathToogleOn, std::string pathToogleOff, const int id, const int posXAux, const int posYAux, const int wAux, const int hAux, const bool active,
		SDL_Renderer* renderer) : ianium::Toggle(id), HudElement(posXAux, posYAux, wAux, hAux, active) {

		toggleOn = false;
		imageOn = new Image(pathToogleOn, renderer);
		imageOff = new Image(pathToogleOff, renderer);

	};
	~Toggle() = default;

	//REDEFINICIONES CLASE UIELEMENT
	// Devuelve la posición (X, Y) del elemento
	virtual std::pair<uint32_t, uint32_t> getPosition() const { return std::make_pair(posX, posY); };
	// Devuelve el tamaño (ancho, alto) del elemento
	virtual std::pair<uint32_t, uint32_t> getSize() const { return std::make_pair(width, height); };
	// Devuelve el estado del elemento
	virtual bool getEnable() const { return isActive; }

	//REDEFINICIONES CLASE TOGGLE
	virtual bool getToggleState() const { return toggleOn; }

	virtual void render(SDL_Renderer* renderer) override {
		rect = { (int)posX,(int)posY,(int)width,(int)height };

		//Activao
		if (toggleOn)
			imageOn->render(rect, renderer);

		//Desactivado
		else
			imageOff->render(rect, renderer);
	}

	virtual void handleInput(const SDL_Event& i_event) {
		int x = i_event.button.x;
		int y = i_event.button.y;
		int n_clicks = i_event.button.clicks;

		// Obtener el estado actual del rat�n
			/*int mouseX, mouseY;
			Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);*/

			// Verificar si se ha pulsado el bot�n izquierdo del rat�n
			//if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
				// Verificar si el rat�n est� dentro de los l�mites del bot�n
		if (x >= posX && x < posX + width && y >= posY && y < posY + height) {
			// Si el bot�n no estaba presionado previamente
			//if (!buttonPressed) {
				// Cambiar el valor del booleano toogleOn
			for (int i = 0; i < n_clicks; i++)
				toggleOn = !toggleOn;
			// Establecer el estado de bot�n como presionado
			//buttonPressed = true;
		//}
		}
		//}
		//else {
		//	// Si se ha soltado el bot�n, establecer el estado de bot�n como no presionado
		//	buttonPressed = false;
		//}
	};

private:
	SDL_Rect rect;
	bool toggleOn;

	Image* imageOn;
	Image* imageOff;
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
	//SDL_Surface* image = IMG_Load("testImage.jpg");
	//Interfaz
	Button* a = new Button("./button.png", 0, 10, 10, 30, 30, true, renderer);
	hud.push_back(a);
	Button* b = new Button("./button.png", 1, 60, 0, 60, 60, true, renderer);
	hud.push_back(b);
	Button* c = new Button("./template.jpg", 2, 0, 300, 355, 255, true, renderer);
	hud.push_back(c);

	Toggle* t = new Toggle("./toggleOn.png", "./toggleOff.png", 3, 500, 300, 100, 100, true, renderer);
	hud.push_back(t);

	//Falta slider por meter
	Slider* s = new Slider("./sliderRange.png", "./sliderButton.png", 4, 200, 200, 200, 20, true, 80.0, 0.0, 100.0, 10, Slider::Orientation::HORIZONTAL, renderer);
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
						elem->handleInput(event);
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