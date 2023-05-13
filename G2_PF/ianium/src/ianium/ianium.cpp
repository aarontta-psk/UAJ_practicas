#include "ianium.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>

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
	switch (uiType)
	{
	case Ianium::UIType::BUTTON:
		if (testableButtons.count(ui_elem->getID())) {
			std::cout << "Button ID " << ui_elem->getID() << " already exists.\n";
			return;
		}
		testableButtons.insert(std::pair<uint32_t, IAButton*>(ui_elem->getID(), static_cast<IAButton*>(ui_elem)));
		break;
	case Ianium::UIType::TOGGLE:
		if (testableToggles.count(ui_elem->getID())) {
			std::cout << "Toggle ID " << ui_elem->getID() << " already exists.\n";
			return;
		}
		testableToggles.insert(std::pair<uint32_t, IAToggle*>(ui_elem->getID(), static_cast<IAToggle*>(ui_elem)));
		break;
	case Ianium::UIType::SLIDER:
		if (testableSliders.count(ui_elem->getID())) {
			std::cout << "Slider ID " << ui_elem->getID() << " already exists.\n";
			return;
		}
		testableSliders.insert(std::pair<uint32_t, IASlider*>(ui_elem->getID(), static_cast<IASlider*>(ui_elem)));
		break;
	default:
		break;
	}
}

bool Ianium::readFolder(const std::string& folderName)
{
	WIN32_FIND_DATAA find_data;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	std::string full_path = PATH + folderName + "\\*";

	hFind = FindFirstFileA(full_path.c_str(), &find_data);
	if (hFind == INVALID_HANDLE_VALUE) {
		return false;
	}

	do {
		//esto comprueba que no sea un directorio
		if (!(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			readScript(PATH + folderName + "/" + find_data.cFileName);
		}
	} while (FindNextFileA(hFind, &find_data) != 0);

	return false;
}

bool Ianium::readScript(const std::string& fileName)
{
	if (fileName.substr(fileName.find_last_of(".") + 1) != "ia") {
		return false;
	}

	std::ifstream file(fileName);

	if (file.fail()) {
		std::cerr << "Error opening file!" << std::endl;
		return false;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::vector<std::string> words;
		std::stringstream ss(line);
		std::string word;
		while (ss >> word) {
			words.push_back(word);
		}
		if (!executeLine(words)) {
			file.close();
			return false;
		}
	}

	file.close();
	return true;
}

bool Ianium::executeLine(const std::vector<std::string>& words)
{	
	if (words[0] == "before") {
		
	}
	else if (words[0] == "test") {
		//aqui las llamadas a todos los tests
	}
	else if (words[0] == "end") {
		//ultima llamada
	}

	return true;
}
