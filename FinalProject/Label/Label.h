#pragma once

#include "../Control/Control.h"
#include <string>

class Label : public Control
{
	string value;
public:
	Label(int width, string value);

	void setValue(string value);
	void draw(Graphics &graphics, int, int, size_t);
	static string centerlizeTxt(int width, string value);
	string getValue();
	void keyDown(WORD, CHAR) {};
	void mousePressed(short, short, bool) {};
	~Label();
};

