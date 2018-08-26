#pragma once

#include "../Panel/Panel.h"
#include "../Button/Button.h"
#include "../Label/Label.h"


class NumericBox : public Panel
{

	struct PlusListener : public MouseListener {
		PlusListener(Control& c) : _c(c) {}
		void mousePressed(Control& b, short x, short y, bool isLeft) {
			NumericBox& tmp = static_cast<NumericBox&>(_c);
			tmp.setValue(tmp.getValue() + 1);
		}
	private:
		Control& _c;
	};


	struct MinusListener : public MouseListener {
		MinusListener(Control& c) : _c(c) {}
		void mousePressed(Control& b, short x, short y, bool isLeft) {
			NumericBox& tmp = static_cast<NumericBox&>(_c);
			tmp.setValue(tmp.getValue() - 1);
		}
	private:
		Control& _c;
	};

	int value;
	int min;
	int max;
public:
	NumericBox(int width, int min, int max);
	void setValue(int val);
	int getValue();
	
};
