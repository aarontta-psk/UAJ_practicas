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

bool Ianium::initPrivate(SDL_Window* sdl_window, SDL_Renderer* sdl_renderer)
{
	if (SDL_WasInit(SDL_INIT_EVERYTHING) == 0 || !sdl_window || !sdl_renderer)
		return false;

	window = sdl_window;
	renderer = sdl_renderer;

	visualTesting = new VisualTesting(window, renderer);
	functionalTesting = new FunctionalTesting(&testableUIElems, renderer);

	return true;
}

void Ianium::releasePrivate()
{
	SDL_Quit();
	delete visualTesting;
}

bool Ianium::readTestDirectoryFiles(const char* rootPath)
{
	WIN32_FIND_DATAA find_data;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	size_t path_len = strlen(rootPath);
	size_t full_path_len = path_len + 3;
	char* full_path = (char*)malloc(full_path_len * sizeof(char));
	if (full_path == 0)
		return false;

	strcpy_s(full_path, full_path_len, rootPath);

	char dir_path[MAX_PATH];

	DWORD ret_val = GetFullPathNameA(full_path, MAX_PATH, dir_path, NULL);

	if (ret_val == 0) {
		std::cout << "No se pudo obtener la ruta absoluta del directorio." << std::endl;
		free(full_path);
		return false;
	}

	if (ret_val > MAX_PATH) {
		std::cout << "La ruta absoluta del directorio es demasiado larga." << std::endl;
		free(full_path);
		return false;
	}

	if (GetFileAttributesA(full_path) == INVALID_FILE_ATTRIBUTES) {
		std::cout << "El directorio especificado no existe." << std::endl;
		free(full_path);
		return false;
	}

	std::cout << "La ruta absoluta del directorio es: " << full_path << std::endl;

	strcat_s(full_path, full_path_len, "\\*");

	hFind = FindFirstFileA(full_path, &find_data);
	if (hFind == INVALID_HANDLE_VALUE) {
		free(full_path);
		return false;
	}

	do {
		//esto comprueba que no sea un directorio
		if (!(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			size_t file_len = strlen(find_data.cFileName);
			size_t full_file_path_len = path_len + file_len + 3;
			char* full_file_path = (char*)malloc(full_file_path_len * sizeof(char));

			if (full_file_path == 0) {
				free(full_path);
				return false;
			}

			strcpy_s(full_file_path, full_file_path_len, rootPath);
			strcat_s(full_file_path, full_file_path_len, "/");
			strcat_s(full_file_path, full_file_path_len, find_data.cFileName);
			readScript(full_file_path);
			free(full_file_path);
		}
	} while (FindNextFileA(hFind, &find_data) != 0);

	free(full_path);
	return true;
}

bool ianium::Ianium::writeTestResults(const char* rootPath)
{
	std::filesystem::path file_path("./Output/" + std::string(rootPath) + ".iaout");

	if (!std::filesystem::exists(file_path.parent_path())) {
		std::filesystem::create_directory(file_path.parent_path());
	}

	std::ofstream file(file_path.string());

	if (file.is_open()) {
		// Escribe en el archivo
		for (auto it = tests.begin(); it != tests.end(); ++it) {
			std::string data;
			if (it->second.passed == true) {
				data = "Tests on script " + std::string(it->second.errorFile) + " succesfully passed \n";
			}
			else {
				data = "Error on script " + std::string(it->second.errorFile) + ", test: " + std::string(it->first) + " line: " + std::string(it->second.errorLine) + " " + std::string(it->second.errorLine) + "\n" +
					"error description: " + std::string(it->second.errorDescription);
			}
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

std::vector<const char*> ianium::Ianium::getWords(std::string line)
{
	std::vector<const char*> words;
	std::stringstream ss(line);
	std::string word_str;

	while (ss >> word_str) {
		char* word = new char[word_str.length() + 1];
		//por que
		strcpy_s(word, word_str.length() + 1, word_str.c_str());
		words.push_back(word);
	}

	return words;
}

bool Ianium::readScript(const char* fileName)
{
	if (strcmp(strrchr(fileName, '.') + 1, "ia") != 0)
		return false;

	std::ifstream file(fileName);

	if (file.fail()) {
		std::cerr << "Error opening file!" << std::endl;
		return false;
	}

	std::string line;
	int nLine = 1;
	while (std::getline(file, line)) {

		std::vector<const char*> first_words = getWords(line);

		if (first_words.size() == 0) {
			nLine++;
			continue;
		}

		if (strcmp(first_words[0], "before:") == 0) {

		}

		else if (strcmp(first_words[0],"test:") == 0) {
			if (first_words.size() != 2) {
				std::string error = "Wrong \"test:\" section label. Try \"test: TEST_NAME\" \n";
				std::cerr << error;
				std::string error_test_name = "error_name_" + std::to_string(error_name);
				std::string errorLine = "test: \n";
				tests.insert(std::make_pair(error_test_name.c_str(), TestInfo(false, fileName, nLine, errorLine.c_str(), error.c_str())));
				error_name++;
				for (const char* ptr : first_words)
					std::free((void*)ptr);
				file.close();
				return false;
			}

			auto test_name = tests.find(first_words[1]);
			if (test_name != tests.end())
			{
				std::string error = "Test name " + std::string(first_words[1]) + " was already in use. \n";
				std::cerr << error;
				std::string error_test_name = "error_name_" + std::to_string(error_name);
				std::string errorLine = "test: " + std::string(first_words[1]) + "\n";
				tests.insert(std::make_pair(error_test_name.c_str(), TestInfo(false, fileName, nLine, errorLine.c_str(), error.c_str())));
				error_name++;
				for (const char* ptr : first_words)
					std::free((void*)ptr);
				file.close();
				return false;
			}

			tests.insert(std::make_pair(first_words[1], TestInfo(false, fileName, 0, nullptr, nullptr)));
			auto test = tests.find(first_words[1]);

			while (std::getline(file, line) && line != "end") {
				nLine++;
				std::vector<const char*> words = getWords(line);

				if (words.size() == 0) {
					nLine++;
					continue;
				}

				if (!executeLine(nLine, words)) {
					for (const char* ptr : words)
						std::free((void*)ptr);
					for (const char* ptr : first_words)
						std::free((void*)ptr);

					file.close();
					std::string error = "Error on script " + std::string(fileName) + " on line " + std::to_string(nLine) + ": \"" + line + "\". Command not recognized." + "\n";
					std::cerr << error;
					test->second.errorLineNumber = nLine;
					test->second.errorLine = line.c_str();
					test->second.errorDescription = error.c_str();
					return false;
				}
				for (const char* ptr : words)
					free((void*)ptr);
			}

			nLine++;

			if (line != "end") {
				std::string error = "Error on script " + std::string(fileName) + ". Missing \"end\" on line " + std::to_string(nLine) + "\n";
				std::cerr << error;
				test->second.errorLineNumber = nLine;
				test->second.errorLine = line.c_str();
				test->second.errorDescription = error.c_str();
				for (const char* ptr : first_words)
					std::free((void*)ptr);
				file.close();
				return false;
			}
			test->second.passed = true;
		}
		else {
			std::string error = "Error on script " + std::string(fileName) + ". Line " + std::to_string(nLine) + "(" + line + ") not recognized as"
				+ " section label of script. Try \"before:\" or \"test: TEST_NAME\". \n";
			std::cerr << error;
			std::string error_test_name = "error_name_" + std::to_string(error_name);
			std::string errorLine = "test: \n";
			tests.insert(std::make_pair(error_test_name.c_str(), TestInfo(false, fileName, nLine, errorLine.c_str(), error.c_str())));
			error_name++;
			for (const char* ptr : first_words)
				std::free((void*)ptr);
			file.close();
			return false;
		}
		nLine++;

		for (const char* ptr : first_words)
			std::free((void*)ptr);
	}
	file.close();
	
	return true;
}

bool Ianium::executeLine(int nLine, const std::vector<const char* >& words)
{	
	// igual esto es un poco xd
#define CHECK_ARG_SIZE(nElems, size, nLine) \
	if (size != nElems) { \
	std::cerr << "Wrong number of arguments on line " << nLine << std::endl; \
	return false; }

#define CHECK_CORRECT_TYPES(code, nLine) \
	try { \
		code; \
	} \
	catch (std::invalid_argument) { \
		std::cerr << "Wrong types of arguments on line " << nLine << std::endl; \
		return false; }

	if (strcmp(words[0], "click") == 0) {
		CHECK_ARG_SIZE(3, words.size(), nLine)
		int x, y;

		CHECK_CORRECT_TYPES(x = std::stoi(words[1]); y = std::stoi(words[2]); , nLine);

		functionalTesting->click(x, y);
	}

	else if (strcmp(words[0], "assertButton") == 0) {
		CHECK_ARG_SIZE(3, words.size(), nLine);
		int state, idButton;
		CHECK_CORRECT_TYPES(state = std::stoi(words[2]); idButton = std::stoi(words[1]);, nLine);
		functionalTesting->assertButton(idButton, state);
	}
	else return false;

	return true;
}

std::string Ianium::elemPrefix(UIType uiType) {
	switch (uiType)
	{
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