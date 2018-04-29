#include <stdio.h>
#include <Windows.h>
#include "Label.h"
#include "Textbox.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

	HANDLE in = GetStdHandle(STD_INPUT_HANDLE);

	Label l({ 10,10 }, "Asaf");
	l.setBackground(BACKGROUND_RED);
	l.draw();

	Textbox chk({ 0,0 }, "Zibi", 4, 4);

	chk.draw();

	while (1) {
		INPUT_RECORD ir;
		DWORD count;
		ReadConsoleInput(in, &ir, 1, &count);
		switch (ir.EventType) {
		case KEY_EVENT:
			cout << ir.Event.KeyEvent.uChar.AsciiChar << " pressed, but ingnored" << '\r';
		}
	}




}