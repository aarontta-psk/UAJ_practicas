#pragma once
#ifndef IANIUM_H
#define IANIUM_H

#include <string>
#include <memory>
#include <set>
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
		std::string test_name;
		uint32_t script_count, test_count;
		uint32_t passed;

		uint32_t errorLineNumber;
		std::string errorFile, errorLine, errorDescription;

		TestInfo(std::string _test_name, uint32_t _script_count, uint32_t _test_count, uint32_t _passed, 
			std::string _errorFile, int _errorLineNumber, std::string _errorLine, std::string _errorDescription)
			: test_name(_test_name), script_count(_script_count), test_count(_test_count), passed(_passed), errorFile(_errorFile),
			errorLineNumber(_errorLineNumber), errorLine(_errorLine), errorDescription(_errorDescription) {};
	};

	struct TestInfoCompare {
		bool operator() (const TestInfo& lhs, const TestInfo& rhs) const {
			return lhs.script_count < rhs.script_count || (lhs.script_count == rhs.script_count && lhs.test_count < rhs.test_count);
		}
	};

	struct TestInfoFind {
		TestInfoFind(const std::string& _name) : name(_name) {}
		bool operator()(const TestInfo& tInfo) {
			return tInfo.test_name == name;
		}
	private:
		std::string name;
	};

	class IANIUM_EXPORT Ianium {
	public:
		Ianium();
		~Ianium();

		/// <summary>
		/// return Ianium singleton instance.
		/// </summary>
		/// <returns>Ianium instance</returns>
		static Ianium* Instance();
		/// <summary>
		/// Initialise Ianium singleton. Requires SDL to have been pre-initialised, and to give the window and renderer to it.
		/// </summary>
		/// <param name="sdl_window">SDL window created by the application</param>
		/// <param name="sdl_renderer">SDL renderer created by the application</param>
		/// <returns>true if correctly initialised, false if not</returns>
		static bool Init(SDL_Window* sdl_window, SDL_Renderer* sdl_renderer);
		/// <summary>
		/// Releases Ianium singleton.
		/// </summary>
		static void Release();

		/// <summary>
		/// Adds an UI element to the list of elements that can be tested.
		/// </summary>
		/// <param name="uiType">UI element type</param>
		/// <param name="ui_elem">UI element object</param>
		void addTestableUIElem(UIType uiType, UIElement* ui_elem);

		/// <summary>
		/// Runs all tests from a given folder. Tis folder has to be on the same hierarchy level as the executable.
		/// </summary>
		/// <param name="rootPath">Path to all script test files</param>
		void runTests(const char* rootPath);

	private:
		static std::unique_ptr<Ianium> instance;

		VisualTesting* visualTesting;
		FunctionalTesting* functionalTesting;

		std::unordered_map<std::string, UIElement*> testableUIElems;

		SDL_Window* window;
		SDL_Renderer* renderer;

		std::set<TestInfo, TestInfoCompare> tests;
		int error_name, script_count, test_count;

		bool initPrivate(SDL_Window* sdl_window, SDL_Renderer* sdl_renderer);
		void releasePrivate();

		/// <summary>
		/// Reads all files, processing all the ones with the .ia extension
		/// </summary>
		/// <param name="rootPath">Name of the root path of the tests' scripts</param>
		/// <returns>true if folder exists, false if it doesn't</returns>
		bool readTestDirectoryFiles(std::string rootPath);
		/// <summary>
		/// Writes the result of the tests processed into a file, in the ./output directory
		/// (same hierarchy level as the executable)
		/// </summary>
		/// <param name="rootPath">Name of the root path of the tests' scripts, used to name the output file</param>
		/// <returns>true if file has been created properly exists, false if wasn't possible to be created</returns>
		bool writeTestResults(std::string rootPath);

		/// <summary>
		/// Reads all tests from a given script file.
		/// </summary>
		/// <param name="fileName">File to be processed</param>
		/// <returns></returns>
		bool readScript(std::string fileName);
		/// <summary>
		/// Executes a command from a test.
		/// </summary>
		/// <param name="nLine">Line where it was read</param>
		/// <param name="words">Words on that given line</param>
		/// <returns>TEST_PASSED (0) if the line has been processed properly, TEST_WRONG_FORMAT if the format of the command is wrong</returns>
		int executeLine(int nLine, const std::vector<std::string>& words);
		/// <summary>
		/// Gets words from a line, separated by spaces.
		/// </summary>
		/// <param name="line">Line to process</param>
		/// <returns>Words present on the given line</returns>
		std::vector<std::string> getWords(std::string line);

		/// <summary>
		/// Returns the prefix ID of each type of UI element.
		/// </summary>
		/// <param name="uiType">UI element type</param>
		/// <returns>prefix ID</returns>
		std::string elemPrefix(UIType uiType);
	};
}
#endif // IA_TOGGLE_H