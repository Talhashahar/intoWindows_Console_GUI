#include "EventEngine.h"

EventEngine::EventEngine(DWORD input, DWORD output)
	: _console(GetStdHandle(input)), _graphics(output)
{
	GetConsoleMode(_console, &_consoleMode);
	SetConsoleMode(_console, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

void EventEngine::run(Control &c)
{
	for (bool redraw = true;;)
	{
		if (redraw)
		{
			_graphics.resetColors();
			_graphics.clearScreen();
			_graphics.setCursorVisibility(false);
			for (size_t p = 0; p < 3; p++) {
				c.draw(_graphics, 0, 0, p);
			}
			redraw = false;
			Control * focused = Control::getFocus();
			if (dynamic_cast<TextBox *>(focused) != NULL) {
				static_cast<TextBox *>(focused)->moveCurser(_graphics);
			}
		}

		INPUT_RECORD record;
		DWORD count;
		ReadConsoleInput(_console, &record, 1, &count);
		switch (record.EventType)
		{
		case KEY_EVENT:
		{
			auto f = Control::getFocus();
			if (f != nullptr && record.Event.KeyEvent.bKeyDown)
			{
				auto code = record.Event.KeyEvent.wVirtualKeyCode;
				auto chr = record.Event.KeyEvent.uChar.AsciiChar;
				if (code == VK_TAB) {
					if (!Panel::getMsgOpen()){
						moveFocus(c, f);
					}
				}
				else
					f->keyDown(code, chr);
				redraw = true;
			}
			break;
		}
		case MOUSE_EVENT:
		{
			auto button = record.Event.MouseEvent.dwButtonState;
			auto coord = record.Event.MouseEvent.dwMousePosition;
			auto x = coord.X;
			auto y = coord.Y;
			if (button == FROM_LEFT_1ST_BUTTON_PRESSED || button == RIGHTMOST_BUTTON_PRESSED)
			{
				c.mousePressed(x, y, button == FROM_LEFT_1ST_BUTTON_PRESSED);
				redraw = true;
			}
			break;
		}
		default:
			break;
		}
	}
}

EventEngine::~EventEngine()
{
	SetConsoleMode(_console, _consoleMode);
}

void EventEngine::moveFocus(Control &main, Control *focused)
{
	vector<Control*> controls;
	main.getAllControls(controls);
	auto it = find(controls.begin(), controls.end(), focused);
	do{
		if (++it == controls.end())
			it = controls.begin();
	}
	while (!(*it)->canGetFocus());
	Control::setFocus(*it);
}