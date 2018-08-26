#include "Panel.h"

const int CONSTANT = 2;

Panel::Panel(int height, int width) : Control(width) {
	setHeight(height);
}

bool Panel::validSpace(Control* ctrl) {

	if (ctrl->getTop() < getBodyTop() || ctrl->getLeft() < getBodyLeft())
		return false;
	if ((ctrl->getTop() + ctrl->getHeight()) > (getBodyTop() + this->getHeight() - CONSTANT))
		return false;
	if ((ctrl->getLeft() + ctrl->getWidth() - CONSTANT) > (getBodyLeft() + this->getWidth() - CONSTANT))
		return false;

	if (!(ctrl->getLayer() - CONSTANT)) return true;
	return validSpaceWithControllers(ctrl);
}

void Panel::getAllControls(vector<Control *> &cont) {

	int cSize = controls.size(), i = 0;

	while (i < cSize) {
		cont.push_back(controls[i]);
		i++;
	}
}

bool Panel::addControl(Control *control, short x, short y) {

	control->setLocation({ x , y });

	if (validSpace(control)) {
		controls.push_back(control);
		return true;
	}

	return false;
}

bool Panel::validSpaceWithControllers(Control* ctrl) {
	
	bool tmpflag = true;
	int cSize = controls.size();

	for (int i = 0; i < cSize; i++) {
		if (!(controls[i]->getLayer() - CONSTANT)) continue;
		if (!controls[i]->validSpace(ctrl)) {
			tmpflag = false;
			break;
		}
	}

	return tmpflag;

}

void Panel::mousePressed(short x, short y, bool isLeft) {

	if (x < this->getLeft() || (x > this->getLeft() + this->getWidth())) return;
	if (y < this->getTop() || (y > this->getTop() + this->getHeight())) return;

	int size = controls.size();
	for (int i = 0; i < size; i++) {
		controls[i]->mousePressed(x, y, isLeft);
	}
}

void Panel::draw(Graphics &g, int x, int y, size_t layer) {

	int i = 0, cSize = controls.size();

	if (!isVisible()) { 
		return;
	}

	if (layer == getLayer()) {
		Control::draw(g, getLeft(), getTop(), layer);
	}

	g.setBackground(g.convertToColor(getBackGround()));
	g.setForeground(g.convertToColor(getForeground()));

	while (i < cSize) {

		g.moveTo(controls[i]->getBodyLeft(), controls[i]->getBodyTop());
		controls[i]->draw(g, controls[i]->getBodyLeft(), controls[i]->getBodyTop(), layer);
	
		++i;
	}
	
	g.resetColors();
}

void Panel::setLocation(COORD coord) {

	COORD crd = {getBodyLeft(),getBodyTop()};
	int cSize = controls.size();

	Control::setLocation(coord);

	for (size_t i = 0; i < cSize; i++) {
		controls[i]->setLocation({ coord.X + controls[i]->getBodyLeft() - crd.X, coord.Y + controls[i]->getBodyTop() - crd.Y });
	}

}

void Panel::closeButtonMessage(){
	isMsgBoxOpen = false;
}

void Panel::openButtonMessage() {
	isMsgBoxOpen = true;
}

bool Panel::getMsgOpen(){
	return isMsgBoxOpen;
}

Panel::~Panel() {
	int cSize = controls.size();
	for (int i = 0; i < cSize; i++) {
		free(controls[i]);
	}
}
