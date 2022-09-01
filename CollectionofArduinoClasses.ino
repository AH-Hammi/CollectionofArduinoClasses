#include "KeyValuePairs.h"
#include "SCPI_Parser/SCPI.h"

Vector<int> elements;

void(* resetFunc) (void) = 0;

void addElement(int newElem){
	Serial.println("Adding Element");
	Serial.println(newElem);
	elements.push_back(newElem);
}

void showList(){
	Serial.println("Showing List");
	Serial.println("Size: " + String(elements.size()));
	Serial.println("Capacity: " + String(elements.capacity()));
	Serial.println("Elements:");
	for (int i = 0; i < elements.size(); i++){
		Serial.println(elements[i]);
	}
}

SCPI_Command* commands[]{
	new SCPI_Command_Numeric<int>("ADD", addElement),
	new SCPI_Command("SHOW", showList),
	new SCPI_Command("QUIT", [](){
		Serial.println("Quitting");
		delay(100);
		resetFunc();
	})
};

SCPI_Parser parser(commands, sizeof(commands) / sizeof(SCPI_Command*));

void setup()
{
	Serial.begin(38400);
	Serial.println("Hello World!");
}

void loop()
{
	
}

void serialEvent()
{
	parser.processCommands(Serial.readStringUntil('\n'));
}