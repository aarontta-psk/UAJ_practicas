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
		/// Finds the number of occurrences of a template image inside another one. Uses internally OpenCV to get a mask and separates 
		/// the connected regions to get how many images were detected
		/// </summary>
		/// <param name="imagePath">Original image where the template image is searched on</param> 
		/// <param name="templateImagePath">Template image</param>  
		/// <returns>Number of occurrences of the template image inside the original image</returns> 
		std::vector<std::pair<double, double>> template_matching(std::string imagePath, std::string templateImagePath);
	};
};
#endif // IA_VISUAL_TESTING_H