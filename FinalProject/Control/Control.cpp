#include "Control.h"



Control::Control(int _width) : 
	width(_width), isFocused(false), isfocusable(true), visible(true), height(1), layer(0){
	setBorder(BorderType::None);
	setLocation({ 0, 0 });
	width += 2;
	height += 2;
	background = BackgroundColor::Black;
	foreground = ForegroundColor::White;
}



void Control::setLayer(int l) {
	layer = l;
}

void Control::focus(){
	isFocused = true;
}
void Control::unfocus(){
	isFocused = false;
}
void Control::setForeground(ForegroundColor color){
	foreground = color;
}
void Control::setBackGround(BackgroundColor color){
	background = color;
}

void Control::hide() {
	visible = false;
	isfocusable = false;
}

void Control::show() {
	visible = true;
	isfocusable = true;
}

int Control::getLayer() {
	return layer;
}

ForegroundColor Control::getForeground(){
	return foreground;
}
BackgroundColor Control::getBackGround(){
	return background;
}

void Control::setBorder(BorderType type){
	borderType = type;
}

BorderType Control::getBorderType(){
	return borderType;
}
char Control::getBorderTypeHorizontal(){

	BorderType tempBorder = getBorderType();
	if(tempBorder== BorderType::Single) 
		return 196;
	if (tempBorder == BorderType::Double) 
		return 205;
	return NULL;
}
char Control::getBorderTypeVertical(){

	BorderType tempBorder = getBorderType();
	if (tempBorder == BorderType::Single) 
		return 179;
	if (tempBorder == BorderType::Double) 
		return 186;
	return NULL;
}

vector<int> Control::getBorderTypeCorners(){
	BorderType tempBorder = getBorderType();
	if (tempBorder == BorderType::Single) 
		return{ 218, 191 , 192, 217 };
	if (tempBorder == BorderType::Double) 
		return{ 201, 187, 200 , 188 };
	return{ 0 , 0, 0, 0 };
}

void Control::setLocation(COORD coord){
	location = coord;
	bodyLocation = { coord.X + 1, coord.Y + 1 };
}

COORD Control::getLocation(){
	return location;
}
void Control::draw(Graphics &g, int x, int y, size_t _width){
	int i = 0;

	if (isFocus()) {
		g.setForeground(g.convertToColor(ForegroundColor::Green));
	} 
	else {
		g.setForeground(g.convertToColor(getForeground()));
	}

	g.setBackground(g.convertToColor(getBackGround()));
	
	string str(width, getBorderTypeHorizontal());
	vector<int> corners = getBorderTypeCorners();

	str[0] = corners[0];
	str[width - 1] = corners[1];

	g.write(getLeft(), getTop(), str);
	
	while (i < height-1) {
		string strv(width, ' ');
		strv[0] = getBorderTypeVertical();
		strv[width - 1] = getBorderTypeVertical();
		g.write(getLeft(), (getTop() + 1) + i, strv);
		i++;
	}
	
	str[0] = corners[2];
	str[width - 1] = corners[3];
	g.write(location.X, location.Y + (height - 1), str);
	g.resetColors();
}

void Control::mousePressed(short x, short y, bool isLeft){
	if (x < this->getLeft() || (x > this->getLeft() + this->getWidth())) 
		return;

	if (y < this->getTop() || (y > this->getTop() + this->getHeight())) 
		return;

	Control::setFocus(this);
}

bool Control::canGetFocus(){
	return isfocusable;
}
bool Control::validSpace(Control* ctrl){
	if ((ctrl->getLeft() + ctrl->getWidth()) < getLeft() ||
		(getLeft() + getWidth()) < ctrl->getLeft()) {
		return true;
	}
	else if ( (ctrl->getTop() + ctrl->getHeight() ) > getTop() ||
		(getTop() + getHeight()) < ctrl->getTop()) {
		return true;;
	}
	return false;
}
bool Control::isFocus(){
	return isFocused;
}
bool Control::isVisible(){
	return visible;
}
short Control::getLeft(){
	return location.X;
}
short Control::getTop(){
	return location.Y;
}

short Control::getBodyLeft(){
	return bodyLocation.X;
}
short Control::getBodyTop(){
	return bodyLocation.Y;
}

int Control::getWidth(){
	return width;
}
int Control::getHeight(){
	return height;
}

void Control::setHeight(int _height) {
	height = _height;
}

void Control::setWidth(int _width) {
	width = _width;
}

	
void Control::setFocus(Control* ctrl){
	if (currentFocused != NULL)
		currentFocused->unfocus();
	currentFocused = ctrl;
	ctrl->focus();
}

Control* Control::getFocus(){
	return currentFocused;
}


Control::~Control(){
	// Default Destructor
}