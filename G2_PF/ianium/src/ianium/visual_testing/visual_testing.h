#pragma once
#ifndef IA_VISUAL_TESTING_H
#define IA_VISUAL_TESTING_H

#include <vector>
#include <string>

#include <common/macros.h>

struct SDL_Window;
struct SDL_Renderer;

namespace ianium {
	class IANIUM_EXPORT VisualTesting {
	public:
		VisualTesting(SDL_Window* sdl_window, SDL_Renderer* sdl_renderer);
		~VisualTesting();

		/// <summary>
		/// Asserts that a certain image is present on the SDL window.
		/// </summary>
		/// <param name="imagePath">Image to be searched on screen</param>
		/// <returns>true if the image appears on screen, false if it doesn't</returns>
		bool assertImageOnScreen(std::string imagePath);

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;

		/// <summary>
		/// Takes a screenshot of the SDL window.
		/// </summary>
		void takeScreenshot();
		/// <summary>
		///
		/// </summary>
		/// <param name="imagePath"></param>
		/// <param name="templateImagePath"></param>
		/// <returns></returns>
		std::vector<std::pair<double, double>> template_matching(std::string imagePath, std::string templateImagePath);
	};
};
#endif // IA_VISUAL_TESTING_H