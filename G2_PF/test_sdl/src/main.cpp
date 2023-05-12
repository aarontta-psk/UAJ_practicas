#include <ui/button.h>
#include <ianium/ianium.h>

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
	Ianium::Instance()->testOPENCV();
	Ianium::Release();

	return 0;
}