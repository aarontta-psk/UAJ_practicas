#include <ianium/testable_ui/button.h>
#include <ianium/ianium.h>
#include <iostream>
#include <fstream>

class Button : public IAButton {
public:
	Button(int id, int posX, int posY, int w, int h, bool active, const char* menu) : IAButton(id, posX, posY, w, h, active, menu) {};
	~Button() = default;
};

int main() {
	Ianium::Init("NOT NEEDED RIGHT NOW CHANGE THIS");
	Button a = Button(0, 0, 0, 0, 0, 0, "u");
	Button b = Button(1, 0, 0, 0, 0, 0, "e");
	Button c = Button(2, 0, 0, 0, 0, 0, "4");
	Ianium::Instance()->visualTesting->testOPENCV("./tempAssets/testImage.jpg");
	try
	{
		//Ianium::Instance()->visualTesting.template_matching("./tempAssets/imageSource.jpg", "./tempAssets/template.jpg");");
		Ianium::Instance()->visualTesting->takeScreenshot();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl; // output exception message
	}
	Ianium::Release();

	return 0;
}