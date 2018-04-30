#include <stdio.h>
#include <Windows.h>
#include "Label.h"
#include "Textbox.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

	HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
	Textbox chk({ 4,4 }, "Fifa 18", 10, 4);

	chk.draw();
	int counter = 0;
	while (1) {
		INPUT_RECORD ir;
		DWORD count;
		ReadConsoleInput(in, &ir, 1, &count);
		chk.HandleEvent(ir, &counter);
	}

}