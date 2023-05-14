#include "ianium.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <cstring>

#include <SDL2/SDL.h>
#include <opencv2/opencv.hpp>

#include <ianium/testable_ui/ui_element.h>
#include <ianium/testable_ui/button.h>
#include <ianium/testable_ui/toggle.h>
#include <ianium/testable_ui/slider.h>

std::unique_ptr<Ianium> Ianium::instance = nullptr;

Ianium::Ianium() = default;

Ianium::~Ianium() = default;

Ianium* Ianium::Instance() {
	return instance.get();
}

bool Ianium::Init() {
	instance.reset(new Ianium());

	//if (!instance.get()->initPlatform()) {
	//	instance.reset(nullptr);
	//	return false;
	//}
	SDL_Init(SDL_INIT_EVERYTHING);

	return true;
}

void Ianium::Release() {
	if (instance.get() == nullptr)
		return;

	//instance.get()->closePlatform();
	SDL_Quit();

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

	for (auto elem : testableUIElems) {
		if (elem.second->getID() == UI_ID)
			return elem.second->getEnable();
	}
	return false;
}


bool Ianium::readFolder(char* folderName)
{
	WIN32_FIND_DATAA find_data;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	size_t path_len = strlen(PATH);
	size_t folder_len = strlen(folderName);
	size_t full_path_len = path_len + folder_len + 3;
	char* full_path = (char*)malloc(full_path_len * sizeof(char));
	if (full_path == 0)
		return false;

	strcpy_s(full_path, full_path_len, PATH);
	strcat_s(full_path, full_path_len, folderName);
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
			size_t full_file_path_len = path_len + folder_len + file_len + 3;
			char* full_file_path = (char*)malloc(full_file_path_len * sizeof(char));

			if (full_file_path == 0) {
				free(full_path);
				return false;
			}

			strcpy_s(full_file_path, full_file_path_len, PATH);
			strcat_s(full_file_path, full_file_path_len, folderName);
			strcat_s(full_file_path, full_file_path_len, "/");
			strcat_s(full_file_path, full_file_path_len, find_data.cFileName);
			readScript(full_file_path);
			free(full_file_path);
		}
	} while (FindNextFileA(hFind, &find_data) != 0);

	free(full_path);
	return true;
}

bool Ianium::readScript(char* fileName)
{
	if (strcmp(strrchr(fileName, '.') + 1, "ia") != 0) {
		return false;
	}

	std::ifstream file(fileName);

	if (file.fail()) {
		std::cerr << "Error opening file!" << std::endl;
		return false;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::vector<char*> words;
		std::stringstream ss(line);
		std::string word_str;
		while (ss >> word_str) {
			char* word = new char[word_str.length() + 1];
			strcpy_s(word, word_str.length() + 1, word_str.c_str());
			words.push_back(word);
		}
		if (!executeLine(words)) {
			for (auto ptr : words) {
				std::free(ptr);
			}
			file.close();
			return false;
		}
		for (auto ptr : words) {
			free(ptr);
		}
	}
	file.close();
	return true;
}

bool Ianium::executeLine(const std::vector<char*>& words)
{	
	if (strcmp(words[0], "before") == 0) {
		
	}
	else if (strcmp(words[0], "test") == 0) {
		//aqui las llamadas a todos los tests
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