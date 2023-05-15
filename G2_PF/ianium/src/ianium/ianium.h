#pragma once
#ifndef IANIUM_H
#define IANIUM_H

#include <string>
#include <memory>
#include <unordered_map>

#include <common/macros.h>

struct SDL_Window;
struct SDL_Renderer;

namespace ianium {
	class UIElement;

	class VisualTesting;
	class FunctionalTesting;

	struct TestInfo {
		bool passed;
		int errorLineNumber;
		const char* errorLine;

		TestInfo(bool _passed, int _errorLineNumber, char* _errorLine)
			: passed(_passed), errorLineNumber(_errorLineNumber), errorLine(_errorLine) {};
	};

	class IANIUM_EXPORT Ianium {
	public:
		enum class UIType { BUTTON, TOGGLE, SLIDER };

		Ianium();
		~Ianium();

		static Ianium* Instance();
		static bool Init(SDL_Window* sdl_window, SDL_Renderer* sdl_renderer);
		static void Release();

		VisualTesting* visualTesting;
		FunctionalTesting* functionalTesting;

		void addTestableUIElem(UIType uiType, UIElement* ui_elem);
		bool searchActiveUIElement(int UI_ID);

		void runTests(const char* rootPath);

	private:
		static std::unique_ptr<Ianium> instance;

		std::unordered_map<std::string, UIElement*> testableUIElems;

		SDL_Window* window;
		SDL_Renderer* renderer;

		std::unordered_map<const char*, TestInfo> tests;

		bool initPrivate(SDL_Window* sdl_window, SDL_Renderer* sdl_renderer);
		void releasePrivate();

		bool readTestDirectoryFiles(const char* rootPath);
		std::vector<const char*> getWords(std::string line);
		bool readScript(const char* fileName);
		bool executeLine(int nLine, const std::vector<const char*>& words);

		std::string elemPrefix(UIType uiType);
	};
}
#endif // IA_TOGGLE_H