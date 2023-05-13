#include <ui/button.h>
#include <ianium/ianium.h>
#include <iostream>
#include <fstream>

class Button : public IAButton {
public:
	Button(int id, int posX, int posY, int w, int h, bool active, const std::string& menu) : IAButton(id, posX, posY, w, h, active, menu) {};
	~Button() = default;
};

int main() {
	Ianium::Init();
	Ianium::Instance()->addUIElem(new Button(0, 0, 0, 0, 0, 0, "u"));
	Ianium::Instance()->addUIElem(new Button(0, 0, 0, 0, 0, 0, "e"));
	Ianium::Instance()->addUIElem(new Button(0, 0, 0, 0, 0, 0, "4"));
	Ianium::Instance()->addUIElem(new Button(0, 0, 0, 0, 0, 0, "1"));
	Ianium::Instance()->addUIElem(new Button(0, 0, 0, 0, 0, 0, "v"));
	Ianium::Instance()->addUIElem(new Button(0, 0, 0, 0, 0, 0, "z"));
	Ianium::Instance()->visualTesting.testOPENCV("./tempAssets/testImage.jpg");
	try
	{
		Ianium::Instance()->visualTesting.template_matching("./tempAssets/imageSource.jpg", "./tempAssets/template.jpg");
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl; // output exception message
	}
	Ianium::Release();

	return 0;
}