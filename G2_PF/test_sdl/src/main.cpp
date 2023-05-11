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
	Ianium::Instance()->addUIElem(new Button(0, 0, 0, 0, 0, 0, "u"));
	Ianium::Instance()->addUIElem(new Button(0, 0, 0, 0, 0, 0, "u"));
	Ianium::Instance()->addUIElem(new Button(0, 0, 0, 0, 0, 0, "u"));
	Ianium::Release();

	return 0;
}