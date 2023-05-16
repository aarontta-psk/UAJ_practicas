#pragma once
#ifndef VISUAL_TESTING_H
#define VISUAL_TESTING_H

#include <common/macros.h>
#include <vector>
#include <string>

struct SDL_Renderer;
struct SDL_Window;

namespace ianium {
	class IANIUM_EXPORT VisualTesting {
	public:
		VisualTesting(SDL_Window* sdl_window, SDL_Renderer* sdl_renderer);
		~VisualTesting();

		bool assertImageOnScreen(std::string imagePath);

	private:
		SDL_Renderer* renderer;
		SDL_Window* window;

		/// <summary>
		/// Finds the number of occurrences of a template image inside another one. Uses internally OpenCV to get a mask and separates 
		/// the connected regions to get how many images were detected
		/// </summary>
		/// <param name="imagePath"></param> Original image where the template image is searched on
		/// <param name="templateImagePath"></param> Template image 
		/// <returns></returns> Number of occurrences of the template image inside the original image
		std::vector<std::pair<double, double>> template_matching(std::string imagePath, std::string templateImagePath);
		void takeScreenshot();
	};
};
#endif // VISUAL_TESTING_H