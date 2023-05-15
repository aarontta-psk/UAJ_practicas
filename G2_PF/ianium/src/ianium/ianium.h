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
		const char* errorFile;
		const char* errorLine;
		const char* errorDescription;

		TestInfo(bool _passed, const char* _errorFile, int _errorLineNumber, const char* _errorLine, const char* _errorDescription)
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

		std::unordered_map<const char*, TestInfo> tests;
		int error_name;

		bool initPrivate(SDL_Window* sdl_window, SDL_Renderer* sdl_renderer);
		void releasePrivate();

		bool readTestDirectoryFiles(const char* rootPath);
		bool writeTestResults(const char* rootPath);
		std::vector<const char*> getWords(std::string line);
		bool readScript(const char* fileName);
		bool executeLine(int nLine, const std::vector<const char*>& words);

		std::string elemPrefix(UIType uiType);
	};
}
#endif // IA_TOGGLE_H