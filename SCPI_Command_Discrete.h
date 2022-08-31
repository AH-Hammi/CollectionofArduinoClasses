#ifndef SCPI_COMMAND_DISCRETE_H
#define SCPI_COMMAND_DISCRETE_H

#include "SCPI_Command.h"

class StateCommandPair
{
private:
	void (*functionPointer)();
public:
	String stateName = "";
	StateCommandPair(){}
	StateCommandPair(String stateName) {
		this->stateName = stateName;
	}
	StateCommandPair(String stateName, void (*functionPointer)()) {
		this->functionPointer = functionPointer;
		this->stateName = stateName;
	}
	StateCommandPair(char* stateName, void (*functionPointer)()) {
		this->functionPointer = functionPointer;
		this->stateName = String(stateName);
	}
	~StateCommandPair() {}
	virtual void executeFunction(){
		functionPointer();
	}
};

class StateCommandPair_Bool : virtual public StateCommandPair
{
private:
	void (*functionPointer)(bool);
	bool b1;
public:
	StateCommandPair_Bool(char* stateName, void (*functionPointer)(bool), bool b1):StateCommandPair(String(stateName)) {
		this->functionPointer = functionPointer;
		this->b1 = b1;
	}
	StateCommandPair_Bool(String stateName, void (*functionPointer)(bool), bool b1):StateCommandPair(stateName) {
		this->functionPointer = functionPointer;
		this->b1 = b1;
	}
	~StateCommandPair_Bool() {}
	 void executeFunction(){
		functionPointer(b1);
	}
};

class SCPI_Command_Discrete : virtual public SCPI_Command
{
private:
	StateCommandPair** pairs;
	short numberOfStates = 0;
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