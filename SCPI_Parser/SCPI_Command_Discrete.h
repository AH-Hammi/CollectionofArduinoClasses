#ifndef SCPI_COMMAND_DISCRETE_H
#define SCPI_COMMAND_DISCRETE_H

#include "SCPI_Command.h"
#include "../KeyValuePairs.h"

class SCPI_Command_Discrete : virtual public SCPI_Command
{
private:
	KeyValuePairs<String, void (*)()> _stateCommandPairs;
protected:
	void cutCmdStr (String &cmdStr){
		cmdStr = cmdStr.substring(cmdStr.indexOf(' '));
		cmdStr.trim();
	}
public:
	SCPI_Command_Discrete(String tempKey) : SCPI_Command(tempKey){
	}
	SCPI_Command_Discrete(String tempKey, KeyValuePairs<String, void (*)()> stateCommandPairs) : SCPI_Command(tempKey){
		_stateCommandPairs = stateCommandPairs;
	}
	~SCPI_Command_Discrete() {}
	void executeCMD(String stringArguments, String &error){
		cutCmdStr(stringArguments);
		_stateCommandPairs.at(stringArguments)();
	}

	// Command to add a new state command pair
	void addStateCommandPair(String state, void (*functionPointer)()){
		_stateCommandPairs.add(state, functionPointer);
	}
};

#endif