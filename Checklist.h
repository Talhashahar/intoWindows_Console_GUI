#pragma once
#include <string>
#include <Windows.h>
#include <sstream>
#include <iostream>
#include "Checkbox.h"

using namespace std;

class Checklist {
	private:
		COORD position;
		Checkbox *list;
		int listSize;
		HANDLE stdoutHandle;
	public:
		Checklist(int CheckBoxCount, string names[], int X, int Y);
		void HandleInput(INPUT_RECORD inputRecord);
		void Draw();
		void KeyEventHandleing(KEY_EVENT_RECORD keyEvent);
		void MouseEventHandleing(MOUSE_EVENT_RECORD mouseEvent);

		~Checklist();
};
