#include "ianium.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string_view>

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

	return true;
}

void Ianium::Release() {
	if (instance.get() == nullptr)
		return;

	//instance.get()->closePlatform();

	instance.reset(nullptr);
}

void Ianium::addUIElem(UIElement* ui_elem)
{
	uiElems.insert(std::pair<std::string, UIElement*>("elem" + (uiElems.size() + 1), ui_elem));
	std::cout << "elem " << uiElems.size() << " added\n";
}

bool Ianium::readScript(std::string path)
{
	std::ifstream file(path);

	if (file.fail()) {
		std::cerr << "Error opening file!" << std::endl;
		return false;
	}

	std::string line;
	while(std::getline(file, line)) {
		std::vector<std::string> words;
		std::stringstream ss(line);
		std::string word;
		while (ss >> word) {
			words.push_back(word);
		}
		if (!executeLine(words)) {
			return false;
		}
	}

	file.close();
	return true;
}

bool Ianium::executeLine(std::vector<std::string> words)
{
	//switch ()
	//{
	//default:
	//	break;
	//}
	return true;
}
