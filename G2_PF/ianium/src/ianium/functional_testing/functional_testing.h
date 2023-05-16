#pragma once
#ifndef IA_FUNCTIONAL_TESTING_H
#define IA_FUNCTIONAL_TESTING_H

#include <string>
#include <utility>
#include <unordered_map>

#include <common/macros.h>

struct SDL_Renderer;

namespace ianium {
	enum class UIType;
	class UIElement;

	class IANIUM_EXPORT FunctionalTesting {
	public:
		FunctionalTesting(std::unordered_map<std::string, UIElement*>* uiTestElems, SDL_Renderer* sdl_renderer);
		~FunctionalTesting();

		/// <summary>
		/// Clicks an UI element by using it's ID.
		/// </summary>
		/// <param name="uiType">UI element type</param>
		/// <param name="id_elem">UI element ID</param>
		void click(UIType uiType, uint64_t id_elem);
		/// <summary>
		/// Clicks on the screen at an specified spot.
		/// </summary>
		/// <param name="x">X coordinate of the spot</param>
		/// <param name="y">Y coordinate of the spot</param>
		void click(uint32_t x, uint32_t y);
		/// <summary>
		/// Releases a click on the screen at an specified spot.
		/// </summary>
		/// <param name="x">X coordinate of the spot</param>
		/// <param name="y">Y coordinate of the spot</param>
		void releaseClick(uint32_t x, uint32_t y);
		/// <summary>
		/// Double clicks on the screen at an specified spot.
		/// </summary>
		/// <param name="x">X coordinate of the spot</param>
		/// <param name="y">Y coordinate of the spot</param>
		void doubleClick(uint32_t x, uint32_t y);
		/// <summary>
		/// Press on the screen at an specified spot.
		/// </summary>
		/// <param name="x">X coordinate of the spot</param>
		/// <param name="y">Y coordinate of the spot</param>
		void pressedClick(uint32_t x, uint32_t y);
		/// <summary>
		/// Moves the mouse to an specified spot of the screen.
		/// </summary>
		/// <param name="x">X coordinate of the spot</param>
		/// <param name="y">Y coordinate of the spot</param>
		void mouseMotion(uint32_t x, uint32_t y);

		/// <summary>
		/// Asserts if a button has the correct state.
		/// </summary>
		/// <param name="idButton">Button ID</param>
		/// <param name="stateToCheck">State that the button should have</param>
		/// <returns>true if it's correct, false if it isn't</returns>
		bool assertButton(uint64_t idButton, uint32_t stateToCheck);
		/// <summary>
		/// Asserts if a toggle has the correct state.
		/// </summary>
		/// <param name="idToggle">Toggle ID</param>
		/// <param name="stateToCheck">State that the toggle should have</param>
		/// <returns>true if it's correct, false if it isn't</returns>
		bool assertToggle(uint64_t idToggle, uint32_t statetoCheck);
		/// <summary>
		/// Asserts if a sldier has the correct internal value.
		/// </summary>
		/// <param name="idButton">Slider ID</param>
		/// <param name="stateToCheck">Value that the sldier should have</param>
		/// <returns>true if it's correct, false if it isn't</returns>
		bool assertSlider(uint64_t idSlider, float value);

		/// <summary>
		/// Runs a specified number of frames of simulation.
		/// </summary>
		/// <param name="n_frames">Number of frames to simulate</param>
		void runFrames(uint32_t n_frames);

	private:
		std::unordered_map<std::string, UIElement*>* uiElems;
		SDL_Renderer* renderer;

		/// <summary>
		/// Returns the prefix ID of each type of UI element.
		/// </summary>
		/// <param name="uiType">UI element type</param>
		/// <returns>prefix ID</returns>
		std::string elemPrefix(UIType uiType);
	};
};
#endif // IA_FUNCTIONAL_TESTING_H