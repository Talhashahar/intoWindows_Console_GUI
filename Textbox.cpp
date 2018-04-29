#include "Textbox.h"
#include <iostream>

void Textbox::draw() {

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	SetConsoleCursorPosition(out, this->position);
	//std::cout << value;
	SetConsoleTextAttribute(out, info.wAttributes);
	SetConsoleCursorPosition(out, info.dwCursorPosition);
	for (int y = 0; y < _SizeY; ++y) {				//print the Y Axis
		for (int x = 0; x < _SizeX; ++x) {			//print the X Axis
			if (x != 0 && y != 0 && x != _SizeX - 1 && y != _SizeY - 1) {
				std::cout << " ";						// space
				continue;
			}
			if (y == 0 && x == 0) {
				std::cout << '\xDA';						// ┌
			}
			if ((y == 0 || y == _SizeY -1) && (x != 0 || x != _SizeX - 1 )) {
				if (y == _SizeY - 1 && x == 0) {
					std::cout << '\xC0';						// └
				}
				else {
					std::cout << '\xC4';						// ─
				}
			}
			if (y == 0 && x == _SizeX - 1) {
				std::cout << '\xBF' << endl;						//┐
			}
			if (y != 0 && (x == 0 || x == _SizeX -1)) {
				if (y == _SizeY - 1 && x == _SizeX - 1) {
					std::cout << '\xD9' << endl;						// ┘
				}
				else if (x == _SizeX - 1) {
					std::cout << ' ' << ' ' << '\xB3' << endl;

					continue;
				}
				else if (x == 0 && y != _SizeY - 1) {
					std::cout << '\xB3';
				}
				else {
					std::cout << '\xC4';						//│
				}
				

			}
		}
	}
	MoveCurAndReplaceTxt(1,1,this->value);
}

void Textbox::MoveCur(int x, int y) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	this->position.X = x;
	this->position.Y = y;
	SetConsoleCursorPosition(out, position);
}

void Textbox::MoveCurAndReplaceTxt(int x, int y, string text) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(out, position);
	cout << text;
}

void Textbox::HandleEvent(INPUT_RECORD inputRecord, int* counter) {
	switch (inputRecord.EventType) {
	case KEY_EVENT:
		if (!(*counter)) {
			if (inputRecord.Event.KeyEvent.uChar.AsciiChar >= 32 && inputRecord.Event.KeyEvent.uChar.AsciiChar <= 127) {
				AddChar(inputRecord.Event.KeyEvent.uChar.AsciiChar);
			}
			else if (inputRecord.Event.KeyEvent.uChar.AsciiChar == 8) {
				DeleteChar();
			}
			else if (inputRecord.Event.KeyEvent.uChar.AsciiChar == 13) {
				MoveCurAndReplaceTxt(1, getPosition().Y + 1, "");
			}
		}
		if ((*counter) == 0) {
			(*counter)++;
		}
		else {
			(*counter) = 0;
		}
	}
}

void Textbox::AddChar(char ch) {
	if (_SizeX > value.length()) {
		value += ch;
		MoveCurAndReplaceTxt(position.X, position.Y, value);
	}
}
void Textbox::DeleteChar() {						//backspace (no delete button)
	if (value.length() > 0) {
		value = value.substr(0, value.size() - 1);
		cout << '\b' << " " << '\b';						
	}
}

