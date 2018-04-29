
#include <string>
#include <Windows.h>
#include <sstream>


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

	void setValue(string Newval) {
		if (Newval.length() < _SizeX - 1) {
			return;
		}
		else {
			value = Newval.substr(0, _SizeX - 2);
		}
	}


	void draw();
	void MoveCur(int x, int y);
	void HandleEvent(INPUT_RECORD inputRecord, int* counter);
	void AddChar(char ch);
	void DeleteChar();
	void MoveCurAndReplaceTxt(int x, int y, string text);
	~Textbox() {};


};