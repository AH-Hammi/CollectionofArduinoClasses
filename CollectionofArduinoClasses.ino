
#include "ContainerLibrary/Vector.h"

#include "SCPI_Parser/SCPI.h"
//#include "ContainerLibrary/Array.h"

Vector<double> elements;

void(* resetFunc) (void) = 0; //declare reset function @ address 0

SCPI_Command_Numeric<double> add("ADD", [](double newElem){
	Serial.println("Adding Element");
	Serial.println(newElem);
	delay(1000);
	elements.push_back(newElem);
});

SCPI_Command show("SHOW", [](){
	Serial.println("Showing List");
	Serial.println("Size: " + String(elements.size()));
	Serial.println("Capacity: " + String(elements.capacity()));
	Serial.println("Elements:");
	for (int i = 0; i < elements.size(); i++){
		Serial.println(elements[i]);
	}
});

SCPI_Command* commands[]{
	&add,
	&show,
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