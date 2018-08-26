#pragma once

#include <Windows.h>
#include <vector>
#include "../Graphics/Graphics.h"

using namespace std;

enum class BorderType {Single, Double, None};

class Control
{
	int width, height, layer;
	bool isFocused, visible;
	COORD location;
	COORD bodyLocation;
	ForegroundColor foreground;
	BackgroundColor background;
	BorderType borderType;
protected:
	bool isfocusable;
public:
	Control(int width);
	virtual void show();
	virtual void hide();
	int getLayer();
	void setLayer(int);
	void setForeground(ForegroundColor color);
	void setBackGround(BackgroundColor color);
	ForegroundColor getForeground();
	BackgroundColor getBackGround();
	void setBorder(BorderType type);
	virtual void setLocation(COORD);
	COORD getLocation();
	virtual void focus();
	virtual void unfocus();
	BorderType getBorderType();
	char getBorderTypeHorizontal();
	char getBorderTypeVertical();
	vector<int> getBorderTypeCorners();
	virtual void draw(Graphics& graphics, int, int, size_t);
	virtual void keyDown(WORD, CHAR) = 0;
	virtual void mousePressed(short, short, bool) = 0;
	bool canGetFocus();
	bool validSpace(Control* c); 
	bool isFocus();
	bool isVisible();
	short getLeft();
	short getTop();
	short getBodyLeft();
	short getBodyTop();
	int getWidth();
	int getHeight();
	void setHeight(int);
	void setWidth(int);
	virtual void getAllControls(vector<Control *> &controls) {}

	static void setFocus(Control* c);
	static Control* getFocus();

	virtual ~Control();
};

static Control* currentFocused = NULL;
