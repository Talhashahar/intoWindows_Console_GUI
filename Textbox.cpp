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
	
}