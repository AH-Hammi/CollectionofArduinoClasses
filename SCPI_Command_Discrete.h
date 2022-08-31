#ifndef SCPI_COMMAND_DISCRETE_H
#define SCPI_COMMAND_DISCRETE_H

#include "SCPI_Command.h"
#include "KeyValuePairs.h"

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
	SCPI_Command_Discrete(String tempKey, StateCommandPair** commands, short numberOfStates) : SCPI_Command(tempKey){
		this->pairs = commands;
		this->numberOfStates = numberOfStates;
	}
	~SCPI_Command_Discrete() {}
	void init(StateCommandPair** commands, short numberOfStates ){
		this->pairs = commands;
		this->numberOfStates = numberOfStates;
	}
	void executeCMD(String stringArguments, String &error){
		cutCmdStr(stringArguments);
		for (short i = 0; i < numberOfStates; i++)
		{
			if (stringArguments.equalsIgnoreCase(pairs[i]->stateName))
			{
				pairs[i]->executeFunction();;
			}
		}
	}
};

#endif