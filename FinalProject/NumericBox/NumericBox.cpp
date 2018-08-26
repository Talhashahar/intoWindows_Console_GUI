#include "NumericBox.h"



NumericBox::NumericBox(int width, int min, int max):Panel(5,width)
{
	value = min;
	int btnWidth = 2;
	MinusListener* ml = new MinusListener(*this);
	PlusListener* pl = new PlusListener(*this);
	
	Label *lblValue = new Label( width - 10 ,to_string(min));
	lblValue->setForeground(ForegroundColor::Orange);

	Button *minButton = new Button(btnWidth, "<<");
	Button *plsButton = new Button(btnWidth,">>");

	plsButton->addListener(*pl);
	minButton->addListener(*ml);

	this->max = max;
	this->min = min;

	addControl(minButton, getBodyLeft(), getBodyTop());
	addControl(lblValue, getBodyLeft() + minButton->getWidth(), getBodyTop());
	addControl(plsButton, lblValue->getLeft() + lblValue->getWidth(), getBodyTop());
	
	
}


int NumericBox::getValue() {	
	string number;
	string v = static_cast<Label*>(controls[1])->getValue();
	int size = v.length(),  i = 0;//finalNumber,
	while (i < size) {
		if (v.at(i) != '\0') {
			number += v.at(i);
		}
		i++;
	}
	//finalNumber = stoi(number) || 0;
	return stoi(number);
};

void NumericBox::setValue(int v) {
	if ((v >= min) && (v <= max)) {
		static_cast<Label*>(controls[1])->setValue(to_string(v));
		string num1 = to_string(v);
	}
};