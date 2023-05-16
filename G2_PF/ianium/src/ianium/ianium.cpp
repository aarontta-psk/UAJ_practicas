#include "ianium.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <windows.h>
#include <shlwapi.h>
#include <filesystem>

#include <SDL2/SDL.h>
#include <opencv2/opencv.hpp>

#include <ianium/visual_testing/visual_testing.h>
#include <ianium/functional_testing/functional_testing.h>

#include <ianium/testable_ui/ui_element.h>
#include <ianium/testable_ui/button.h>
#include <ianium/testable_ui/toggle.h>
#include <ianium/testable_ui/slider.h>

using namespace ianium;

std::unique_ptr<Ianium> Ianium::instance = nullptr;

Ianium::Ianium() = default;

Ianium::~Ianium() = default;

Ianium* Ianium::Instance() {
	return instance.get();
}

bool Ianium::Init(SDL_Window* sdl_window, SDL_Renderer* sdl_renderer) {
	instance.reset(new Ianium());
	
	if (!instance.get()->initPrivate(sdl_window, sdl_renderer)) {
		instance.reset(nullptr);
		return false;
	}
	return true;
}

void Ianium::Release() {
	if (instance.get() == nullptr)
		return;

	instance->releasePrivate();
	instance.reset(nullptr);
}

void Ianium::addTestableUIElem(UIType uiType, UIElement* ui_elem)
{
	std::string ui_elem_id = elemPrefix(uiType) + std::to_string(ui_elem->getID());
	if (testableUIElems.count(ui_elem_id)) {
		std::cout << "ID " << ui_elem_id << " already exists.\n";
		return;
	}
	testableUIElems.insert(std::pair<std::string, UIElement*>(ui_elem_id, ui_elem));
}

void Ianium::runTests(const char* rootPath) {
	error_name = 0;
	readTestDirectoryFiles(rootPath);
	writeTestResults(rootPath);
	tests.clear();
}

bool Ianium::initPrivate(SDL_Window* sdl_window, SDL_Renderer* sdl_renderer) {
	if (SDL_WasInit(SDL_INIT_EVERYTHING) == 0 || !sdl_window || !sdl_renderer) {
		std::cout << "SDL should have been initialised previously, " <<
			"and the window and renderer sent directly to Ianium through the initialisation.\n";
		return false;
	}

	window = sdl_window;
	renderer = sdl_renderer;

	visualTesting = new VisualTesting(window, renderer);
	functionalTesting = new FunctionalTesting(&testableUIElems, renderer);

	return true;
}

void Ianium::releasePrivate() {
	delete visualTesting;
	delete functionalTesting;

	window = nullptr;
	renderer = nullptr;
}

bool Ianium::readTestDirectoryFiles(std::string rootPath) {
	if (std::filesystem::exists(rootPath))
		for (const auto& archivo : std::filesystem::directory_iterator(rootPath))
			readScript(rootPath + "/" + archivo.path().filename().string());
	else {
		std::cerr << "El directorio especificado no existe." << std::endl;
		return false;
	}

	return true;
}

bool ianium::Ianium::writeTestResults(std::string rootPath) {
	std::filesystem::path file_path("./output/" + rootPath + ".iaout");

	if (!std::filesystem::exists(file_path.parent_path()))
		std::filesystem::create_directory(file_path.parent_path());

	std::ofstream file(file_path.string());

	if (file.is_open()) {
		// Escribe en el archivo
		for (auto it = tests.begin(); it != tests.end(); ++it) {
			std::string data;
			if (it->second.passed == TEST_PASSED)
				data = "[+] Tests on script " + it->second.errorFile + " succesfully passed \n";
			else if (it->second.passed == TEST_FAILED)
				data = "[-] Tests on script " + it->second.errorFile + " failed \n";
			else if (it->second.passed == TEST_WRONG_FORMAT)
				data = "Error on script " + it->second.errorFile + ", test: " + std::string(it->first) + " line: " + std::string(it->second.errorLine) + " " + std::string(it->second.errorLine) + "\n" +
					"error description: " + it->second.errorDescription;
			file << data;
		}
		file.close();
		std::cout << "Archivo creado correctamente." << std::endl;
	}
	else {
		std::cout << "No se pudo crear el archivo." << std::endl;
		return false;
	}
	return true;
}

bool Ianium::readScript(std::string fileName) {
	int longitud = fileName.length();
	std::string extension = fileName.substr(longitud - 3);
	if (extension != ".ia") {
		std::cerr << "Wrong extension" << std::endl;
		return false;
	}

	std::ifstream file(fileName);
	if (file.fail()) {
		std::cerr << "Error opening file!" << std::endl;
		return false;
	}

	std::string line;
	int nLine = 1;
	while (std::getline(file, line)) {
		std::vector<std::string> first_words = getWords(line);
		if (first_words.size() == 0) {
			nLine++;
			continue;
		}

		if (first_words[0] == "before:") {}
		else if (first_words[0] == "test:") {
			if (first_words.size() != 2) {
				std::string error = "Wrong \"test:\" section label. Try \"test: TEST_NAME\" \n";
				std::cerr << error;
				std::string error_test_name = "error_name_" + std::to_string(error_name);
				std::string errorLine = "test: \n";
				tests.insert(std::make_pair(error_test_name, TestInfo(false, fileName, nLine, errorLine, error)));
				error_name++;
				file.close();
				return false;
			}

			auto test_name = tests.find(first_words[1]);
			if (test_name != tests.end()) {
				std::string error = "Test name " + first_words[1] + " was already in use. \n";
				std::cerr << error;
				std::string error_test_name = "error_name_" + std::to_string(error_name);
				std::string errorLine = "test: " + first_words[1] + "\n";
				tests.insert(std::make_pair(error_test_name, TestInfo(false, fileName, nLine, errorLine, error)));
				error_name++;
				file.close();
				return false;
			}

			tests.insert(std::make_pair(first_words[1], TestInfo(false, fileName, 0, "", "")));
			auto test = tests.find(first_words[1]);

			while (std::getline(file, line) && line != "end") {
				nLine++;

				std::vector<std::string> words = getWords(line);
				if (words.size() == 0) {
					nLine++;
					continue;
				}
				int testResult = executeLine(nLine, words);
				switch (testResult) {
					case TEST_WRONG_FORMAT: {
						test->second.passed = TEST_WRONG_FORMAT;
						file.close();
						std::string error = "Error on script " + fileName + " on line " + std::to_string(nLine) + ": \"" + line + "\". Command not recognized." + "\n";
						std::cerr << error;
						test->second.errorLineNumber = nLine;
						test->second.errorLine = line;
						test->second.errorDescription = error;
						return false;
						break;
					}
					case TEST_FAILED:
						test->second.passed = TEST_FAILED;
						break;
					case TEST_PASSED:
						test->second.passed = TEST_PASSED;
						break;
					default:
						break;
				}
				if (testResult == TEST_FAILED) {
					while (std::getline(file, line) && line != "end");
					break; //no more asserts are needed if test fails once
				}
			}
			for (auto elem : testableUIElems)
				elem.second->reset();

			nLine++;

			if (line != "end") {
				std::string error = "Error on script " + fileName + ". Missing \"end\" on line " + std::to_string(nLine) + "\n";
				std::cerr << error;
				test->second.errorLineNumber = nLine;
				test->second.errorLine = line;
				test->second.errorDescription = error;
				file.close();
				return false;
			}
		}
		else {
			std::string error = "Error on script " + fileName + ". Line " + std::to_string(nLine) + "(" + line + ") not recognized as"
				+ " section label of script. Try \"before:\" or \"test: TEST_NAME\". \n";
			std::cerr << error;
			std::string error_test_name = "error_name_" + std::to_string(error_name);
			std::string errorLine = "test: \n";
			tests.insert(std::make_pair(error_test_name, TestInfo(false, fileName, nLine, errorLine, error)));
			error_name++;
			file.close();
			return false;
		}
		nLine++;
	}
	file.close();
	
	return true;
}

int Ianium::executeLine(int nLine, const std::vector<std::string>& words) {	
	int returnValue = TEST_PASSED;
	if (words[0] == "click") {
		CHECK_ARG_SIZE(3, words.size(), nLine)
		int x, y;
		CHECK_CORRECT_TYPES(x = std::stoi(words[1]); y = std::stoi(words[2]); , nLine);
		functionalTesting->click(x, y);
	}
	else if (words[0] == "clickElem") {
		CHECK_ARG_SIZE(3, words.size(), nLine)
			int type, id;
		CHECK_CORRECT_TYPES(type = std::stoi(words[1]); id = std::stoi(words[2]); , nLine);
		switch (type)
		{
			case (int)UIType::BUTTON:
			case (int)UIType::TOGGLE:
			case (int)UIType::SLIDER:
				break;
			default:
				return TEST_WRONG_FORMAT;
				break;
		}
		functionalTesting->click(type, id);
	}
	else if (words[0] == "clickUp") {
		CHECK_ARG_SIZE(3, words.size(), nLine);
		int x, y;
		CHECK_CORRECT_TYPES(x = std::stoi(words[1]); y = std::stoi(words[2]);, nLine);
		functionalTesting->pressedClick(x, y);
	}
	else if (words[0] == "mouseMotion") {
		CHECK_ARG_SIZE(3, words.size(), nLine);
		int x, y;
		CHECK_CORRECT_TYPES(x = std::stoi(words[1]); y = std::stoi(words[2]); , nLine);
		functionalTesting->mouseMotion(x, y);
	}
	else if (words[0] == "assertButton") {
		CHECK_ARG_SIZE(3, words.size(), nLine);
		int state, idButton;
		CHECK_CORRECT_TYPES(state = std::stoi(words[2]); idButton = std::stoi(words[1]);, nLine);
		functionalTesting->assertButton(idButton, state) ? returnValue = TEST_PASSED : returnValue = TEST_FAILED;
	}
	else if (words[0] == "assertToggle") {
		CHECK_ARG_SIZE(3, words.size(), nLine);
		int state, idToggle;
		CHECK_CORRECT_TYPES(state = std::stoi(words[2]); idToggle = std::stoi(words[1]); , nLine);
		functionalTesting->assertToggle(idToggle, state) ? returnValue = TEST_PASSED : returnValue = TEST_FAILED;
	}
	else if (words[0] == "assertSlider") {
		CHECK_ARG_SIZE(3, words.size(), nLine);
		int idSlider;
		float value;
		CHECK_CORRECT_TYPES(value = std::stoi(words[2]); idSlider = std::stoi(words[1]);, nLine);
		functionalTesting->assertSlider(idSlider, value) ? returnValue = TEST_PASSED : returnValue = TEST_FAILED;
	}
	else if (words[0] == "assertImageOnScreen") {
		CHECK_ARG_SIZE(2, words.size(), nLine);
		std::string templateImgPath = words[1];
		visualTesting->assertImageOnScreen(templateImgPath) ? returnValue = TEST_PASSED : returnValue = TEST_FAILED;
	}
	else if (words[0] == "runFrames") {
		CHECK_ARG_SIZE(2, words.size(), nLine);
		int frames;
		CHECK_CORRECT_TYPES(frames = std::stoi(words[1]);, nLine);
		functionalTesting->runFrames(frames);
	}
	
	else return TEST_WRONG_FORMAT;

	return returnValue;
}

std::vector<std::string> ianium::Ianium::getWords(std::string line)
{
	std::vector<std::string> words;
	std::stringstream ss(line);
	std::string word_str;

	while (ss >> word_str)
		words.push_back(word_str);
	return words;
}

std::string Ianium::elemPrefix(UIType uiType) {
	switch (uiType) {
	case UIType::BUTTON:
		return "button_";
		break;
	case UIType::TOGGLE:
		return "toggle_";
		break;
	case UIType::SLIDER:
		return "slider_";
		break;
	default:
		return "";
		break;
	}
}