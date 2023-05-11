#include "ianium.h"

#include <iostream>

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