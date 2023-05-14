#pragma once
#ifndef IANIUM_H
#define IANIUM_H

#include <string>
#include <memory>
#include <unordered_map>

#include <common/macros.h>
#include <ianium/visual_testing/visual_testing.h>
#include <ianium/functional_testing/functional_testing.h>

class VisualTesting;
class FunctionalTesting;

class UIElement;

class IANIUM_EXPORT Ianium {
public:
	enum class UIType { BUTTON, TOGGLE, SLIDER };

	Ianium();
	~Ianium();

	static Ianium* Instance();
	static bool Init(const char* rootPath);
	static void Release();

	VisualTesting visualTesting;
	FunctionalTesting functionalTesting;

	void addTestableUIElem(UIType uiType, UIElement* ui_elem);
	bool readFolder(char* folderName);

private:
	static std::unique_ptr<Ianium> instance;

	std::unordered_map<std::string, UIElement*> testableUIElems;

	std::string elemPrefix(UIType uiType);

	bool readScript(char* fileName);
	bool executeLine(const std::vector<char*>& words);

	const char* rootPath;
};
#endif // IA_TOGGLE_H