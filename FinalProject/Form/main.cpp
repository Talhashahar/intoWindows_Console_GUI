#include <string>
#include "../Panel/Panel.h"
#include "../CheckList/CheckList.h"
#include "../ComboBox/ComboBox.h"
#include "../Graphics/Graphics.h"
#include "../TextBox/TextBox.h"
#include "../RadioList/RadioList.h"
#include "../EventEngine/EventEngine.h"
#include "../NumericBox/NumericBox.h"
#include "../MessegeBox/MsgBox.h"

using namespace std;

struct MyListener : public MouseListener
{
	MyListener(Control &c) : _c(c) { }
	void mousePressed(Control& b, short x, short y, bool isLeft)
	{
		_c.show();
		Control::setFocus(&_c);
	}
private:
	Control &_c;
};


int main(void){	
	const int WI = 20;
	const int MAX_WI = 85;
	Panel form(35, 100);	
	EventEngine engine;

	//Titles
	Label lblTitle1(MAX_WI, "CPP-FINAL-PROJECT");
	Label lblTitle2(MAX_WI, "Registration Details:");	
	
	lblTitle1.setForeground(ForegroundColor::Cyan);
	lblTitle2.setForeground(ForegroundColor::Cyan);
	lblTitle2.setBackGround(BackgroundColor::White);

	//FullName
	Label lblName(WI, "Full Name: ");
	TextBox txtName(WI);
	txtName.setValue("John Doe");
	txtName.setBorder(BorderType::Single);

	//Email
	Label lblEmail(WI, "Email: ");
	TextBox txtEmail(WI);
	txtEmail.setValue("john@gmail.com");
	txtEmail.setBorder(BorderType::Single);

	//Age
	Label lblAge(WI, "Age: ");
	NumericBox numAge(WI, 18, 99);
	numAge.setBorder(BorderType::Double);
	numAge.setValue(18);

	//Gender
	Label lblGender(WI, "Gender: ");
	RadioList radGender(8, WI, { "Male", "Female"});
	
	//Knowledge
	Label lblKnowledge(WI, "Knowledge:");
	CheckList chkKnowledge(14, WI, { "C", "C++", "JAVA", "PYTHON" });

	//Status
	Label lblStatus(WI, "Status: ");
	ComboBox comboStatus(WI, { "Single", "Married", "Divorced"});

	//MsgBox
	MsgBox msgBox(20, 50);
	msgBox.hide();
	msgBox.setBorder(BorderType::Double);
	msgBox.setBackGround(BackgroundColor::Blue);
	msgBox.setForeground(ForegroundColor::White);

	//ButtonRegister
	MyListener* listener = new MyListener(msgBox);
	Button btnReg(15, "   Register");
	btnReg.setForeground(ForegroundColor::Red);
	btnReg.addListener(*listener);
	btnReg.setBorder(BorderType::Single);

	/*addElementsToForm*/
	form.setBorder(BorderType::Double);

	form.addControl(&msgBox, 20, 5);

	form.addControl(&lblTitle1, 5, 1);	
	form.addControl(&lblTitle2, 5, 3);
	
	form.addControl(&lblName, 1, 7);
	form.addControl(&txtName, WI, 7);
	
	form.addControl(&lblEmail, 1, 10);
	form.addControl(&txtEmail, WI, 10);

	form.addControl(&lblAge, 1, 13);
	form.addControl(&numAge, WI, 13);
	
	form.addControl(&lblGender, 1, 18);
	form.addControl(&radGender, WI, 18);

	form.addControl(&lblKnowledge, 50, 7);
	form.addControl(&chkKnowledge, 50+WI, 7);

	form.addControl(&lblStatus, 50, 20);
	form.addControl(&comboStatus, 50+WI, 20);
	
	form.addControl(&btnReg, 42, 27);
	

	Control::setFocus(&txtName);	
	engine.run(form);	
		
	return msgBox.getResult();
}