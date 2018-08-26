#include "Label.h"


Label::Label(int width, string value):Control(width)
{
	isfocusable = false;
	if (width - value.size() < 2) 
		this->value = value;
	else {
		this->value = centerlizeTxt(width, value);
	}
}

string Label::getValue() {
	return value;
}

void Label::setValue(string val) {
	value = centerlizeTxt(getWidth() - 2, val);
}

string Label::centerlizeTxt(int width, string value) {

	string txt;

	txt.resize(width - value.length());
	txt.insert(((width / 2) - (value.length() / 2)), value);

	return txt;

}

void Label::draw(Graphics &g, int x , int y, size_t layer) {

	size_t tempLayer = getLayer();

	if (tempLayer != layer) 
		return;

	Control::draw(g, x, y, layer);
	g.setBackground(g.convertToColor(getBackGround()));
	g.setForeground(g.convertToColor(getForeground()));
	g.write(getBodyLeft(),getBodyTop(), value);
	g.resetColors();

}

Label::~Label()
{
}