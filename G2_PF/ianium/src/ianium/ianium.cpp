#include "ianium.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <windows.h>
#include <shlwapi.h>

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

bool Ianium::searchActiveUIElement(int UI_ID) {

	for (auto elem : testableUIElems)
		if (elem.second->getID() == UI_ID)
			return elem.second->getEnable();
	return false;
}

void Ianium::runTests(const char* rootPath) {
	readTestDirectoryFiles(rootPath);
}

bool Ianium::initPrivate(SDL_Window* sdl_window, SDL_Renderer* sdl_renderer)
{
	if (SDL_WasInit(SDL_INIT_EVERYTHING) == 0 || !sdl_window || !sdl_renderer)
		return false;

	window = sdl_window;
	renderer = sdl_renderer;

	visualTesting = new VisualTesting(window, renderer);
	functionalTesting = new FunctionalTesting();

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
	while (std::getline(file, line)) {
		std::vector<const char*> words;
		std::stringstream ss(line);
		std::string word_str;
		while (ss >> word_str) {
			char* word = new char[word_str.length() + 1];
			strcpy_s(word, word_str.length() + 1, word_str.c_str());
			words.push_back(word);
		}
		if (!executeLine(words)) {
			for (const char* ptr : words)
				std::free((void*)ptr);
			file.close();
			return false;
		}
		for (const char* ptr : words)
			free((void*)ptr);
	}
	file.close();
	return true;
}

bool Ianium::executeLine(const std::vector<const char* >& words)
{	
	if (strcmp(words[0], "before") == 0) {
		
	}
	else if (strcmp(words[0], "test") == 0) {
		if (strcmp(words[1], "click") == 0) {
			int x = std::stoi(words[2]);
			int y = std::stoi(words[3]);
			functionalTesting->click(x, y);
		}
	}
	else if (strcmp(words[0], "end") == 0) {
		//ultima llamada
	}

	return true;
}

std::string Ianium::elemPrefix(UIType uiType) {
	switch (uiType)
	{
	case Ianium::UIType::BUTTON:
		return "button_";
		break;
	case Ianium::UIType::TOGGLE:
		return "toggle_";
		break;
	case Ianium::UIType::SLIDER:
		return "slider_";
		break;
	default:
		return "";
		break;
	}
}