#include "Textbox.h"
#include <iostream>


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
			if (inputRecord.Event.KeyEvent.uChar.AsciiChar >= 32 && inputRecord.Event.KeyEvent.uChar.AsciiChar <= 127) {		//all charts in english and numbers
				AddChar(inputRecord.Event.KeyEvent.uChar.AsciiChar);
			}
			else if (inputRecord.Event.KeyEvent.uChar.AsciiChar == 8) {															//backsapce
				DeleteChar();
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
	stringstream ss;
	string temp;
	if (_SizeX > value.length() +2 ) {					//append the char to string and replace the text on specific cords
		if (ch == ' ') {
			temp = value + " ";

			MoveCurAndReplaceTxt(position.X, position.Y, temp);
		}
		else {
			ss << ch;
			ss >> temp;
			value += temp;
			MoveCurAndReplaceTxt(position.X, position.Y, value);
		}	
	}
}
void Textbox::DeleteChar() {						//backspace (no delete button)
	if (value.length() > 0) {
		value = value.substr(0, value.size() - 1);
		cout << '\b' << " " << '\b';						
	}
}


void Textbox::draw() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;

	//int x = position.X;
	//int y = position.Y;
	int YAxis = 0;
	int x;
	MoveCur(position.X, position.Y);
	for (x = 0; x < _SizeX; ++x) {
		if (x == 0) {
			std::cout << '\xDA';						// ┌
			continue;
		}
		if (x != _SizeX - 1) {
			std::cout << '\xC4';						// ─
			continue;
		}
		if (x == _SizeX - 1) {
			std::cout << '\xBF';						//┐
		}
	}
	MoveCur(position.X, position.Y+1);
	for (x = 0; x < _SizeX; ++x) {
		if (x == 0 || x == _SizeX -1) {
			std::cout << '\xB3';					//|
		}
		else {
			std::cout << ' ';						//space
		}
	}
	MoveCur(position.X, position.Y + 1);	
	for (x = 0; x < _SizeX; ++x) {
		if (x == 0) {
			std::cout << '\xC0';						// └
			continue;
		}
		if (x != _SizeX - 1) {
			std::cout << '\xC4';						// ─
			continue;
		}
		if (x == _SizeX - 1) {
			std::cout << '\xD9' << endl;						// ┘
		}
	}
	MoveCurAndReplaceTxt(position.X+1, position.Y -1, value);
}

