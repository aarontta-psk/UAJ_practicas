#pragma once
#ifndef IANIUM_H
#define IANIUM_H

#include <string>
#include <memory>
#include <unordered_map>

#include <common/macros.h>

class UIElement;

class IANIUM_EXPORT Ianium {
public:
	Ianium();
	~Ianium();

	static Ianium* Instance();
	static bool Init();
	static void Release();

	void addUIElem(UIElement* ui_elem);

private:
	static std::unique_ptr<Ianium> instance;

	std::unordered_map<std::string, UIElement*> uiElems;
};
#endif // IA_TOGGLE_H