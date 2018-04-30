#include "Checklist.h"

Checklist::Checklist(int CheckBoxCount, string names[], int X, int Y) {
	this->position.X = X;
	this->position.Y = Y;
	this->listSize = CheckBoxCount;
	this->stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	this->list = new Checkbox[this->listSize];
	if (this->list == nullptr) {
		cout << "The allocation failed, exit.";
		exit(0);
	}
	for (int i = 0; i < this->listSize; ++i) {
		this->list[i].SetText(names[i]);
		this->list[i].SetX(X);
		this->list[i].SetY(Y + i);
		this->list[i].SetKeyboardFocus(false);
	}
	this->list[0].SetKeyboardFocus(true);				//by defualt make focus for first checkbox;
}

void Checklist::Draw() {
	SetConsoleCursorPosition(stdoutHandle, position);
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	GetConsoleScreenBufferInfo(stdoutHandle, &consoleScreenBufferInfo);

	CONSOLE_CURSOR_INFO consoleCursorInfo = { 100, FALSE };
	SetConsoleCursorInfo(stdoutHandle, &consoleCursorInfo);

	for (int i = 0; i < listSize; ++i) {
		SetConsoleCursorPosition(stdoutHandle, this->list[i].getCoords());
		this->list[i].Draw();
	}
}

void Checklist::HandleInput(INPUT_RECORD inputRecord) {			//run handle the input, if this keyboard input run keyboard method work also with mouse input.
	if (inputRecord.EventType == KEY_EVENT) {
		this->KeyEventHandleing(inputRecord.Event.KeyEvent);
	}
	else {
		MouseEventHandleing(inputRecord.Event.MouseEvent);
	}
}

void Checklist::KeyEventHandleing(KEY_EVENT_RECORD keyEvent) {
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	GetConsoleScreenBufferInfo(stdoutHandle, &consoleScreenBufferInfo);

	Checkbox *item = nullptr;
	int Currectitem;
	if (keyEvent.bKeyDown == true) {
		for (int i = 0; i < this->listSize; ++i) {
			if (this->list[i].GetKeyboardFocus() == true) {
				item = &this->list[i];
				Currectitem = i;
				break;
			}
		}
		if (item == nullptr) {
			return;
		}
		if (keyEvent.wVirtualKeyCode == VK_DOWN) {
			item->SetKeyboardFocus(false);
			if (Currectitem == this->listSize - 1) {
				item = &this->list[0];
				item->SetKeyboardFocus(true);
				Currectitem = 0;
			}
			else {
				++Currectitem;
				item = &this->list[Currectitem];
				item->SetKeyboardFocus(true);
			}
			return;
		}
		if (keyEvent.wVirtualKeyCode == VK_UP) {
			item->SetKeyboardFocus(false);
			if (Currectitem == 0) {
				Currectitem = this->listSize - 1;
				this->list[Currectitem].SetKeyboardFocus(true);
			}
			else {
				--Currectitem;
				this->list[Currectitem].SetKeyboardFocus(true);
			}
			return;
		}	
		if (keyEvent.wVirtualKeyCode == VK_SPACE) {
			SetConsoleCursorPosition(stdoutHandle, this->list[Currectitem].getCoords());
			this->list[Currectitem].Choose();
			return;
		}
	}
}

void Checklist::MouseEventHandleing(MOUSE_EVENT_RECORD mouseEvent) {
	COORD mCords = mouseEvent.dwMousePosition;
	if (mouseEvent.dwEventFlags == 0) {
		if (mouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			for (int i = 0; i < this->listSize; ++i) {
				if (this->list[i].IsTarget(mCords)) {
					SetConsoleCursorPosition(stdoutHandle, this->list[i].getCoords());
					this->list[i].Choose();
					break;										//no chance for more checkbox to click.
				}
			}
		}
	}
}



Checklist::~Checklist() {
	delete[] this->list;
}