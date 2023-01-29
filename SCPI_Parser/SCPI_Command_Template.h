/**
 * @file SCPI_Command_Template.h
 * @author Alexander Hammans (a.hammans@kostal.com)
 * @brief This file contains a template class for SCPI_Command
 * @version 0.1
 * @date 20.12.2022
 * This Class only serves as a build stone for further command type.
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SCPI_COMMAND_TEMPLATE_H
#define SCPI_COMMAND_TEMPLATE_H

#include "SCPI_Command.h"

/**
 * @brief This class represents a single SCPI command
 * 
 * @tparam NT Type of the parameter from the function
 */
template <typename NT>
class SCPI_Command_Template : public SCPI_Command
{
public:
	/**
	 * @brief Pointer to the function that should be executed when the command is called
	 * 
	 */
	void (*functionPointer) (NT);

	SCPI_Command_Template() :SCPI_Command("EMPTY"){
	}

	/**
	 * @brief Construct a new SCPI_Command_Template object
	 * 
	 * @param key The SCPI command key
	 * @param functionPointer Pointer to the function that should be executed when the command is called
	 */
	SCPI_Command_Template(String tempKey, void (*in)(NT)) :SCPI_Command(tempKey){
		functionPointer = in;
	}

	~SCPI_Command_Template() {}

	/**
	 * @brief Execute the function
	 * Does nothing, needs to be overwritten by the child class
	 */
	virtual void executeCMD(String stringArguments, String &error){
		return;
	}
};

#endif
