#pragma once
#ifndef MACROS_H
#define MACROS_H
#define IANIUM_EXPORT __declspec(dllexport)

//maybe this could be done better
#define CHECK_ARG_SIZE(nElems, size, nLine) \
	if (size != nElems) { \
	std::cerr << "Wrong number of arguments on line " << nLine << std::endl; \
	return false; }

#define CHECK_CORRECT_TYPES(code, nLine) \
	try { \
		code; \
	} \
	catch (std::invalid_argument) { \
		std::cerr << "Wrong types of arguments on line " << nLine << std::endl; \
		return false; }

#endif // MACROS_H