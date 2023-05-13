#include "functional_testing.h"

#include <iostream>

void FunctionalTesting::test(const char* path)
{
	std::cout << "Failed to read, " << path << "not found" << std::endl;
}