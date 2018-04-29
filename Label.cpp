#include "Label.h"
#include <iostream>

void Label::setForeground(DWORD fg) {
	this->fg = fg;
}

void Label::setBackground(DWORD bg) {
	this->bg = bg;
}

void Label::draw() {

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	SetConsoleCursorPosition(out,this->position);
	SetConsoleTextAttribute(out, this->fg | this->bg);
	std::cout << value;
	SetConsoleTextAttribute(out, info.wAttributes);
	SetConsoleCursorPosition(out, info.dwCursorPosition);
}