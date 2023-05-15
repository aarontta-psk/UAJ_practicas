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
	enum class UIType;
	class UIElement;

	class VisualTesting;
	class FunctionalTesting;

	struct TestInfo {
		bool passed;
		int errorLineNumber;
		std::string errorFile;
		std::string errorLine;
		std::string errorDescription;

		TestInfo(bool _passed, std::string _errorFile, int _errorLineNumber, std::string _errorLine, std::string _errorDescription)
			: passed(_passed), errorFile(_errorFile), errorLineNumber(_errorLineNumber), errorLine(_errorLine), errorDescription(_errorDescription) {};
	};

	class IANIUM_EXPORT Ianium {
	public:

		Ianium();
		~Ianium();

		static Ianium* Instance();
		static bool Init(SDL_Window* sdl_window, SDL_Renderer* sdl_renderer);
		static void Release();

		void addTestableUIElem(UIType uiType, UIElement* ui_elem);
		void runTests(const char* rootPath);

	private:
		static std::unique_ptr<Ianium> instance;

		VisualTesting* visualTesting;
		FunctionalTesting* functionalTesting;

		std::unordered_map<std::string, UIElement*> testableUIElems;

		SDL_Window* window;
		SDL_Renderer* renderer;

		std::unordered_map<std::string, TestInfo> tests;
		int error_name;

		bool initPrivate(SDL_Window* sdl_window, SDL_Renderer* sdl_renderer);
		void releasePrivate();

		bool readTestDirectoryFiles(std::string rootPath);
		bool writeTestResults(std::string rootPath);
		std::vector<std::string> getWords(std::string line);
		bool readScript(std::string fileName);
		bool executeLine(int nLine, const std::vector<std::string>& words);

		std::string elemPrefix(UIType uiType);
	};
}
#endif // IA_TOGGLE_H