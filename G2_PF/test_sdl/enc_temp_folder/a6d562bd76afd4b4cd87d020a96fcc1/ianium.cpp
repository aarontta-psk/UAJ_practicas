#include "ianium.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>

#include <SDL.h>

#include "opencv2/opencv.hpp"

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

void Ianium::addUIElem(UIElement* ui_elem)
{
	uiElems.insert(std::pair<std::string, UIElement*>("elem" + (uiElems.size() + 1), ui_elem));
	std::cout << "elem " << uiElems.size() << " added\n";

	SDL_Event eventee = { SDL_QUIT };
	SDL_PushEvent(&eventee);
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

void Ianium::testOPENCV()
{
	cv::Mat image = cv::imread("./testImage.jpg");
	cv::imshow("testImage", image);
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
