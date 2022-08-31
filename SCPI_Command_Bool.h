#ifndef SCPI_COMMAND_BOOL_H
#define SCPI_COMMAND_BOOL_H

#include "SCPI_Command_Discrete.h"

class SCPI_Command_Bool : virtual public SCPI_Command_Discrete
{
private:
	void (*functionPointerBool) (bool);
public:
	SCPI_Command_Bool(void (*in)(bool), String tempKey) : SCPI_Command_Discrete(tempKey),SCPI_Command(tempKey){
		functionPointerBool = in;
		StateCommandPair* pairs[] = {new StateCommandPair_Bool(String("ON"),functionPointerBool,true), new StateCommandPair_Bool(String("1"),functionPointerBool,true), new StateCommandPair_Bool("OFF",functionPointerBool,false), new StateCommandPair_Bool("0",functionPointerBool,false)};
		SCPI_Command_Discrete::init(pairs,sizeof(pairs));
	}
	~SCPI_Command_Bool() {}
	void executeCMD(String stringArguments, String &error){
		cutCmdStr(stringArguments);
		if ((stringArguments.equalsIgnoreCase("ON")|| stringArguments.equalsIgnoreCase("1"))){
			functionPointerBool(true);
		}else if ((stringArguments.equalsIgnoreCase("OFF")|| stringArguments.equalsIgnoreCase("0"))){
			functionPointerBool(false);
		}else{
			Serial.println("WRONG ARGUMENT");
		}
	}
};

#endif