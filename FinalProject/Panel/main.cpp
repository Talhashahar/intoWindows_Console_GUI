#include <string>
#include "../EventEngine/EventEngine.h"
#include "Panel.h"


using namespace std;

int main(int argc, char **argv) {
	Panel panel(25, 50);
	panel.setLocation({ 3, 0 });
	panel.setBorder(BorderType::Double);
	EventEngine engine;
	engine.run(panel);
}