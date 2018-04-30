#include <stdio.h>
#include <Windows.h>
#include "Label.h"
#include "Textbox.h"
#include <string>
#include <iostream>
#include "Checklist.h"

using namespace std;

void textboxfunc();
void checkboxfunc();

int main(int argc, char** argv) {

	//textboxfunc();
	checkboxfunc();
	

}

void textboxfunc() {
	HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
	Textbox chk({ 4,4 }, "Fifa 18", 10, 4);

	chk.draw();
	int counter = 0;
	while (true) {
		INPUT_RECORD ir;
		DWORD count;
		ReadConsoleInput(in, &ir, 1, &count);
		chk.HandleEvent(ir, &counter);
	}
}

void checkboxfunc() {
	string items[] = {"Fifa 18", "Fifa 17", "Fifa 16"};
	Checklist Mylist(3, items, 1, 1);
	Mylist.Draw();
	HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
	while (true) {
		INPUT_RECORD inputRecord;
		DWORD count;
		ReadConsoleInput(in, &inputRecord, 1, &count);
		Mylist.HandleInput(inputRecord);
	}
}