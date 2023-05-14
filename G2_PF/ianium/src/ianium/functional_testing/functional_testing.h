#pragma once
#ifndef FUNCTIONAL_TESTING_H
#define FUNCTIONAL_TESTING_H

#include <common/macros.h>

namespace ianium {
	class IANIUM_EXPORT FunctionalTesting {
	public:
		void test(const char* path);

		void click(int x, int y);

		void doubleClick(int x, int y);

		void pressedClick(int x, int y);

		void clickUp(int x, int y);

		void click(int id_elem);

		bool IsElemOnMenu(int id_elem);

		bool Assert();
	};
};
#endif // FUNCTIONAL_TESTING_H