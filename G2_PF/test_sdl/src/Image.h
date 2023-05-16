#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Image {
public:
	Image(std::string path, SDL_Renderer* renderer);

	~Image();

	void render(SDL_Rect rect, SDL_Renderer* renderer);

private:
	uint32_t w, h;
	SDL_Texture* texture;
	SDL_Surface* surface;
};

