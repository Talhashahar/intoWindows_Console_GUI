
#include <string>
#include <Windows.h>

using namespace std;

class Textbox
{
private:
	COORD position;
	string value;
	int _SizeX;
	int _SizeY;

public:

	Textbox(COORD pos, string name, int SizeX, int SizeY)
		: position(pos), value(name), _SizeX(SizeX), _SizeY(SizeY) {
	};

	string getValue() {
		return value;
	}

	COORD getPosition() {
		return position;
	}


	void draw();

	void draw(int w, int h);

	~Textbox() {};


};