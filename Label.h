#pragma once

#include <string>
#include <Windows.h>

using namespace std;

class Label
{
private:
	COORD position;
	string value;
	DWORD bg;
	DWORD fg;

public:
	
	Label(COORD pos, string name) 
		: position(pos), value(name) {
		this->bg = 0;
		this->fg = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	};

	string getValue() {
		return value;
	}

	COORD getPosition() {
		return position;
	}

	void setBackground(DWORD bg);
	void setForeground(DWORD fg);

	void draw();

	~Label() {};


};

