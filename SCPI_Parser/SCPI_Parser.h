/**
 * @file SCPI_Parser.h
 * @author Alexander Hammans (a.hammans@kostal.com)
 * @brief SCPI Parser Class
 * @version 1.0
 * @date 20.12.2022
 * This class interprets Strings and processes them to parse SCPI Commands
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SCPI_PARSER_H
#define SCPI_PARSER_H

#include "SCPI_Command.h"	// Include the header of SCPI_Command Class

/**
 * @brief SCPI Parser Class
 * A class to Interpret a String and process its content to parse SCPI Commands
 */
class SCPI_Parser
{
private:
	/**
	 * @brief Pointer to an array with the Commands the Parser should interpret
	 */
	SCPI_Command** _commands;
	/**
	 * @brief The number of Commands in the array
	 */
	int _commandsSize;

	// TODO: Add error handling
	String errors;

	/**
	 * @brief Internal method,Extract the Command from a String
	 * This method extracts the Command from a String. It removes all characters before the first space and converts the String to lower case.
	 * @param cmdStr The String to extract the Command from
	 * @return String The extracted Command
	 */
	String extractCommand(String cmdStr){
		cmdStr.remove(cmdStr.indexOf(' '));
		cmdStr.toLowerCase();
		return cmdStr;
	}

	/**
	 * @brief Internal method, to process one command
	 * This method processes one command. It removes all characters before the first alphanumeric character or * and then searches for a matching command in the command list. If a match is found, the command is executed.
	 * @param cmdStr 
	 */
	void processOneCommand(String cmdStr){
		while (!(isAlphaNumeric(cmdStr[0]) || cmdStr[0] == '*')&& cmdStr != ""){
			cmdStr = cmdStr.substring(1);
		}
		if (cmdStr!=""){
			for(int i=0; i<_commandsSize; i++){
				if(_commands[i]->isKey(extractCommand(cmdStr))){
					Serial.println("Found Match");
					Serial.println(_commands[i]->key);
					_commands[i]->executeCMD(cmdStr,errors);
					break;
				}
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
		newSemicolon = cmdString.indexOf(';'); 
		while (newSemicolon >= 0){
			cutStr = cmdString.substring(0,newSemicolon);
			cmdString = cmdString.substring(newSemicolon+1);
			processOneCommand(cutStr);
			newSemicolon = cmdString.indexOf(';'); 
		}
		processOneCommand(cmdString);
	}

	String returnError(){
		return errors;
	}
};

#endif
