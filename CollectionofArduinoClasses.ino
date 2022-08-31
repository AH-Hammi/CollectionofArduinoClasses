#include "KeyValuePairs.h"
#include "SCPI_Parser.h"
#include "SCPI_Command.h"
#include "SCPI_Command_Numeric.h"

Vector<float> elements;

void addElement(float newElem){
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
	new SCPI_Command_Numeric("ADD", addElement),
	new SCPI_Command("SHOW", showList),
	new SCPI_Command("QUIT", NULL)
};

SCPI_Parser parser(commands, sizeof(commands) / sizeof(SCPI_Command*));

void setup()
{
	Serial.begin(38400);
	Serial.println("Hello World!");
	elements.push_back(5.0);
}

void loop()
{
	
}

void serialEvent()
{
	parser.processCommands(Serial.readStringUntil('\n'));
}