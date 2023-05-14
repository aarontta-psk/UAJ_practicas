#pragma once
#ifndef IANIUM_H
#define IANIUM_H

#include <string>
#include <memory>
#include <unordered_map>

#include <common/macros.h>
#include <ianium/visual_testing/visual_testing.h>
#include <ianium/functional_testing/functional_testing.h>

#define PATH "../ianium_test/"

class VisualTesting;
class FunctionalTesting;

class UIElement;
class IAButton;
class IAToggle;
class IASlider;

class IANIUM_EXPORT Ianium {
public:
	enum class UIType { BUTTON, TOGGLE, SLIDER };

	Ianium();
	~Ianium();

	static Ianium* Instance();
	static bool Init();
	static void Release();

	VisualTesting visualTesting;
	FunctionalTesting functionalTesting;

	void addTestableUIElem(UIType uiType, UIElement* ui_elem);
	bool readFolder(char* folderName);

private:
	static std::unique_ptr<Ianium> instance;

	std::unordered_map<uint32_t, IAButton*> testableButtons;
	std::unordered_map<uint32_t, IAToggle*> testableToggles;
	std::unordered_map<uint32_t, IASlider*> testableSliders;

	bool readScript(char* fileName);
	bool executeLine(const std::vector<char*>& words);
};
#endif // IA_TOGGLE_H