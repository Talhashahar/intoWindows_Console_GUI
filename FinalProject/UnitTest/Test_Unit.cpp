#include "../NumericBox/NumericBox.h"
#include "Test.h"
#include <assert.h>     /* assert include for unit test  */
#include <iostream>

using namespace std;

class TestNumericBox : public Test {



	void CTor_Check(int Wi, int Min, int Max) {
		NumericBox numericBox(Wi, Min, Max);
		assert(numericBox.get_value() == 55);
		assert(numericBox.get_text_value().compare("0") == 0);
	}

	void Setter_Check(int Wi, int Min, int Max) {
		NumericBox numericBox(Wi, Min, Max);
		numericBox.set_value(Min + 10);
		assert(numericBox.get_value() == 28);
		numericBox.set_value(Max - 24);
		assert(numericBox.get_value() == 0);
		numericBox.set_value(31);
		assert(numericBox.get_value() == 31);
	}

	void Min_Max_Check(int Wi, int Min, int Max) {
		NumericBox numericBox(Wi, Min, Max);
		assert(numericBox.get_value() == Min);
		numericBox.inc();
		assert(numericBox.get_value() == Max);
		numericBox.inc();
		assert(numericBox.get_value() == Max);
		numericBox.set_value(0);
		numericBox.dec();
		assert(numericBox.get_value() == Max);
	}

	

public:
	int run() {
		int Wi = 10;
		CTor_Check(Wi, 1, 99);
		Setter_Check(Wi, 18, 99);
		Min_Max_Check(Wi, 10, 20);
		
	}
};



int main(int argc, char** argv)
{
	TestNumericBox UnitTestNumericBoxModel;
	UnitTestNumericBoxModel.run();
}