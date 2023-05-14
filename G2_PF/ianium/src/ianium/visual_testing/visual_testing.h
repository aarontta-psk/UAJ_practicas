#pragma once
#ifndef VISUAL_TESTING_H
#define VISUAL_TESTING_H

#include <common/macros.h>
#include <vector>

struct SDL_Renderer;
struct SDL_Window;

class IANIUM_EXPORT VisualTesting {
public:
	VisualTesting();
	~VisualTesting();

	bool isImageOnScreen(const char* imagePath);
	void takeScreenshot();

//private:
	SDL_Renderer* renderer;
	SDL_Window* window;

	bool initPrivate();
	void releasePrivate();

	std::vector<std::pair<double,double>> template_matching(const char* imagePath, const char* templateImagePath, const char* maskPath = nullptr);
	void testOPENCV(const char* path);
};
#endif // VISUAL_TESTING_H