#pragma once

#include <string>
#include <Windows.h>


enum class ForegroundColor { Red, Green, Blue, Purple, Teal, Yellow, White, Black, Cyan, Orange };
enum class BackgroundColor { Red, Green, Blue, Purple, Teal, Yellow, White, Black, Cyan, Orange };

using namespace std;

enum class Color { Black, Blue, Green, Red, Cyan, Purple, Orange, White };

class Graphics
{
public:
	Graphics(DWORD stdHandle = STD_OUTPUT_HANDLE);
	void clearScreen();
	void moveTo(int x, int y);
	void setBackground(Color color);
	void setForeground(Color color);
	void resetColors();
	void write(string s);
	void write(int x, int y, string s);
	void write(wstring s);
	void write(int x, int y, wstring s);
	void setCursorVisibility(bool isVisible);
	Color convertToColor(BackgroundColor c);
	Color convertToColor(ForegroundColor c);

private:
	HANDLE _console;
	Color _background, _foreground;

	void updateConsoleAttributes();
};

bool isInside(int x, int y, int left, int top, int width, int height);