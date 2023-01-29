/**
 * @file SCPI_Command_Parameter.h
 * @author Alexander Hammans (a.hammans@kostal.com)
 * @brief This file contains the SCPI_Command_Parameter class which is a SCPI_Command with a SCPI_Parameter for the arguments.
 * @version 1.0
 * @date 23.12.2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef SCPI_COMMAND_PARAMETER_H
#define SCPI_COMMAND_PARAMETER_H

#include "SCPI_Command.h"
#include "SCPI_Parameter.h"

template <int NumberOfParameters>
class SCPI_Command_Parameter : public SCPI_Command
{
private:
	SCPI_Parameter<NumberOfParameters> parameters;

public:
	void (*functionPointer) (SCPI_Parameter<NumberOfParameters> *parameters);
	SCPI_Command_Parameter(){}
	SCPI_Command_Parameter(String key, void (*functionPointer) (SCPI_Parameter<NumberOfParameters> *parameters)) : SCPI_Command(key){
		this->functionPointer = functionPointer;
	}
	~SCPI_Command_Parameter(){}

	virtual void executeCMD(String stringArguments, String &error){
		parameters.setParameters(cutCMDString(stringArguments));
		functionPointer(&parameters);
	}

	void setBounds(byte parameterNumber, double def, double min, double max){
		parameters.setBounds(parameterNumber, def, min, max);
	}
};
#endif
