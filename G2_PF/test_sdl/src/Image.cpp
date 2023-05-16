#include "Image.h"

Image::Image(std::string path, SDL_Renderer* renderer)
{
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

Image::~Image()
{
	std::cout << surface << "\n" << texture << "\n\n";

	SDL_FreeSurface(surface);
	surface = nullptr;

	SDL_DestroyTexture(texture);
	texture = nullptr;

}

void Image::render(SDL_Rect rect, SDL_Renderer* renderer)
{
	if (texture) {
		SDL_RenderCopy(renderer, texture, nullptr, &rect);
	}
	else {
		// Cuadrado rosita
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
		SDL_RenderFillRect(renderer, &rect);
	}
}
