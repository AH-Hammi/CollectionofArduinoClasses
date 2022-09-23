#ifndef SCPI_COMMAND_BOOL_H
#define SCPI_COMMAND_BOOL_H

#include "SCPI_Command_Template.h"

class SCPI_Command_Bool : public SCPI_Command_Template<bool>
{
private:
	void cutCmdStr (String &cmdStr){
		cmdStr = cmdStr.substring(cmdStr.indexOf(' '));
		cmdStr.trim();
	}
public:
	SCPI_Command_Bool(String tempKey, void (*in)(bool)) :SCPI_Command_Template<bool>(tempKey,in){
	}
	~SCPI_Command_Bool() {}
	void executeCMD(String stringArguments, String &error){
		cutCmdStr(stringArguments);
		if ((stringArguments.equalsIgnoreCase("ON")|| stringArguments.equalsIgnoreCase("1"))){
			functionPointer(true);
		}else if ((stringArguments.equalsIgnoreCase("OFF")|| stringArguments.equalsIgnoreCase("0"))){
			functionPointer(false);
		}else{
			Serial.println("WRONG ARGUMENT");
		}
	}
};

#endif
