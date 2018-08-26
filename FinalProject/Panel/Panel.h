#pragma once

#include "../Control/Control.h"
#include <vector>

using namespace std;

class Panel : public Control
{
	bool validSpaceWithControllers(Control* c);
protected:
	vector<Control *> controls;

public:
	Panel(int height, int width);
	virtual bool addControl(Control *control, short, short);
	bool validSpace(Control* c); 
	void getAllControls(vector<Control *> &controls);
	void draw(Graphics &graphics, int, int, size_t);
	virtual void mousePressed(short, short, bool);
	virtual void keyDown(WORD, CHAR){}
	void setLocation(COORD);
	static bool getMsgOpen();
	static void openButtonMessage();
	static void closeButtonMessage();

	~Panel();
};

static bool isMsgBoxOpen = false;
