#pragma once
#ifndef FUNCTIONAL_TESTING_H
#define FUNCTIONAL_TESTING_H

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

		void click(UIType uiType, uint64_t id_elem);
		void click(int x, int y);
		void clickUp(int x, int y);
		void doubleClick(int x, int y);
		void pressedClick(int x, int y);
		void mouseMotion(int x, int y);

		bool isElemOnMenu(int id_elem);
		bool assertT();

		void run(uint32_t n_frames);

	private:
		std::unordered_map<std::string, UIElement*>* uiElems;
		SDL_Renderer* renderer;

		std::string elemPrefix(UIType uiType);
	};
};
#endif // FUNCTIONAL_TESTING_H