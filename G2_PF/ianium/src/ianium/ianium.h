#pragma once
#ifndef IANIUM_H
#define IANIUM_H

#include <string>
#include <memory>
#include <unordered_map>

#include <common/macros.h>
#include <ianium/visual_testing/visual_testing.h>
#include <ianium/functional_testing/functional_testing.h>

struct SDL_Window;
struct SDL_Renderer;

namespace ianium {
	class UIElement;

	class VisualTesting;
	class FunctionalTesting;

	class IANIUM_EXPORT Ianium {
	public:
		enum class UIType { BUTTON, TOGGLE, SLIDER };

		Ianium();
		~Ianium();

		static Ianium* Instance();
		static bool Init(const char* rootPath, SDL_Window* sdl_window, SDL_Renderer* sdl_renderer);
		static void Release();

		VisualTesting* visualTesting;
		FunctionalTesting functionalTesting;

		void addTestableUIElem(UIType uiType, UIElement* ui_elem);
		bool readFolder();

		bool searchActiveUIElement(int UI_ID);

	private:
		static std::unique_ptr<Ianium> instance;

		std::unordered_map<std::string, UIElement*> testableUIElems;

		SDL_Window* window;
		SDL_Renderer* renderer;

		std::string elemPrefix(UIType uiType);

		bool initPrivate(SDL_Window* sdl_window, SDL_Renderer* sdl_renderer);
		void releasePrivate();

		bool readScript(char* fileName);
		bool executeLine(const std::vector<char*>& words);

		const char* rootPath;
	};
}
#endif // IA_TOGGLE_H