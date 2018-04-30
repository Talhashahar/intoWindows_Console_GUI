#include <string>
#include <Windows.h>
#include <sstream>
#include <iostream>

using namespace std;

class Checkbox {
	private:
		HANDLE stdoutHandle;
		COORD position;
		string value;
		int Lengh;
		bool Checked;
		bool KeyBoardFocus;
	public:
		Checkbox(string text, int x, int y);
		Checkbox();								//std ctor
		//~Checkbox();							//std dtor
		void Draw();
		void Choose();
		bool IsTarget(COORD mCords);
		void SetText(string _value);
		void SetX(int _x);
		void SetY(int _y);
		COORD getCoords();
		bool GetStatus();
		void SetKeyboardFocus(bool f);
		bool GetKeyboardFocus();
		//void FlipKBfocus();
};