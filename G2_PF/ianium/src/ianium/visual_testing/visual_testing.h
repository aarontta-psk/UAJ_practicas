#pragma once
#ifndef VISUAL_TESTING_H
#define VISUAL_TESTING_H

#include <common/macros.h>
#include <vector>

struct SDL_Renderer;
struct SDL_Window;

namespace ianium {
	class IANIUM_EXPORT VisualTesting {
	public:
		VisualTesting(SDL_Window* sdl_window, SDL_Renderer* sdl_renderer);
		~VisualTesting();

		bool isImageOnScreen(const char* imagePath);
		void takeScreenshot();

	private:
		SDL_Renderer* renderer;
		SDL_Window* window;

		std::vector<std::pair<double, double>> template_matching(const char* imagePath, const char* templateImagePath, const char* maskPath = nullptr);
	};
};
#endif // VISUAL_TESTING_H