#pragma once
#ifndef VISUAL_TESTING_H
#define VISUAL_TESTING_H

#include <common/macros.h>

class IANIUM_EXPORT VisualTesting {
public:
	bool template_matching(const char* imagePath, const char* templateImagePath, const char* maskPath = nullptr);
	void testOPENCV(const char* path);
};
#endif // VISUAL_TESTING_H