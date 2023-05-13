#pragma once
#ifndef VISUAL_TESTING_H
#define VISUAL_TESTING_H

#include <common/macros.h>

class IANIUM_EXPORT VisualTesting {
public:
	bool template_matching(const char* imagePath, const char* templateImagePath, const char* maskPath = nullptr);
	void testOPENCV(const char* path);

	int a; 
private:
	/// <summary>
	/// Function used by openCV in template_matching to obtain the matching occurrences
	/// </summary>
	static void matchingMethod(int, void*);
};



#endif