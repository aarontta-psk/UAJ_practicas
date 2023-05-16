#include "Image.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Image::Image(const std::string & path, SDL_Renderer* renderer) : surface(nullptr), texture(nullptr)
{
	surface = IMG_Load(path.c_str());
	if (!surface) {
		std::cout << "Failure loading image " << path << ": " << IMG_GetError() << std::endl;
		return;
	}

	// Crear una textura a partir de la superficie
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		// Manejar error de creación de textura
		std::cout << "Failure creating texture: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(surface);
		surface = nullptr;
		return;
	}

	// Obtener el ancho y alto de la imagen
	w = surface->w;
	h = surface->h;
}

Image::~Image()
{

	if (surface != nullptr) {
		SDL_FreeSurface(surface);
		surface = nullptr;
	}
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void Image::render(SDL_Rect rect, SDL_Renderer* renderer)
{
	if (texture)
		SDL_RenderCopy(renderer, texture, nullptr, &rect);
	else {
		// pink square
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
		SDL_RenderFillRect(renderer, &rect);
	}
}
