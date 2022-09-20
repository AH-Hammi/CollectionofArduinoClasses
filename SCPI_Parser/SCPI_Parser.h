#ifndef SCPI_PARSER_H
#define SCPI_PARSER_H

#include "SCPI_Command.h"	// Include the header of SCPI_Command Class

/**
 * @brief SCPI Parser Class
 * A class to Interpet a Stream and process its content to parse SCPI Commands
 */
class SCPI_Parser
{
private:
	/**
	 * @brief Pointer to an array with the Commands the Parser should interpret
	 */
	SCPI_Command** _commands;
	int _commandsSize;
	String errors;
	String extractCommand(String cmdStr){
		cmdStr.remove(cmdStr.indexOf(' '));
		cmdStr.toLowerCase();
		return cmdStr;
	}
	void processOneCommand(String cmdStr){
		for(int i=0; i<_commandsSize; i++){
			if(_commands[i]->isKey(extractCommand(cmdStr))){
				Serial.println("Found Match");
				Serial.println(_commands[i]->key);
				_commands[i]->executeCMD(cmdStr,errors);
				break;
			}
		}
	}

public:
	SCPI_Parser(SCPI_Command** cmdList, int numberOfCmds) {
		_commands = cmdList;
		_commandsSize = numberOfCmds;
	}
	~SCPI_Parser() {

	}
	void processCommands(String cmdString){
		short newSemicolon = 0;
		String cutStr = "";
		Serial.println("Got a Command");
		while ((cmdString.indexOf(';')) > 0){
			cutStr = cmdString.substring(0,cmdString.indexOf(';'));
			cmdString = cmdString.substring(cmdString.indexOf(';')+1);
			while (!(isAlphaNumeric(cutStr[0]) || cutStr[0] == '*')){
				cutStr = cutStr.substring(1);
			}
			processOneCommand(cutStr);
		}
		if (cmdString != ""){
			while (!(isAlphaNumeric(cmdString[0]) || cmdString[0] == '*')){
				cmdString = cmdString.substring(1);
			}
			processOneCommand(cmdString);
		}
	}

	String returnError(){
		return errors;
	}
};

#endif
