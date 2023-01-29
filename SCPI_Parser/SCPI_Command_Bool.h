/**
 * @file SCPI_Command_Bool.h
 * @author Alexander Hammans (a.hammans@kostal.com)
 * @brief This is the definition of the SCPI_Command_Bool class.
 * @version 1.0
 * @date 20.12.2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SCPI_COMMAND_BOOL_H
#define SCPI_COMMAND_BOOL_H

#include "SCPI_Command.h"

/**
 * @brief This class represents a single SCPI command of type boolean
 * This class handles the execution of a command with a boolean parameter.
 * It is a child class of SCPI_Command.
 * It translates the string parameter to a boolean value and executes the function with the boolean value.
 * It supports the following string values for true: 1, ON, TRUE
 * It supports the following string values for false: 0, OFF, FALSE
 */
class SCPI_Command_Bool : public SCPI_Command
{
private:
	void cutCmdStr (String &cmdStr){
		cmdStr = cmdStr.substring(cmdStr.indexOf(' '));
		cmdStr.trim();
	}
public:
	void (*functionPointer) (bool);
	SCPI_Command_Bool(String tempKey, void (*in)(bool)) :SCPI_Command(tempKey){
		functionPointer = in;
	}
	~SCPI_Command_Bool() {}
	void executeCMD(String stringArguments, String &error){
		cutCmdStr(stringArguments);
		stringArguments.toUpperCase();
		if ((stringArguments == "ON"|| stringArguments == "1" || stringArguments == "TRUE")){
			functionPointer(true);
		}else if ((stringArguments == "OFF"|| stringArguments == "0" || stringArguments == "FALSE")){
			functionPointer(false);
		}else{
			Serial.println("WRONG ARGUMENT");
		}
	}
};

#endif
