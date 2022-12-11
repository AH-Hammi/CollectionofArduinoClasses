#ifndef SCPI_COMMAND_ONE_PARAM_H
#define SCPI_COMMAND_ONE_PARAM_H

#include "SCPI_Command_Template.h"
#include "SCPI_Parameter.h"

template <typename NT>
class SCPI_Command_One_Param : public SCPI_Command_Template<NT>
{
private:
	void cutCmdStr (String &cmdStr){
		cmdStr = cmdStr.substring(cmdStr.indexOf(' '));
		cmdStr.trim();
	}
	SCPI_Parameter parameter(NT);	
public:
	SCPI_Command_One_Param() :SCPI_Command_Template<NT>("EMPTY",NULL){
	}
	SCPI_Command_One_Param(const char *tempKey, void (*in)(NT)) :SCPI_Command_Template<NT>(tempKey,in){
	}
	SCPI_Command_One_Param(String tempKey, void (*in)(NT)) :SCPI_Command_Template<NT>(tempKey,in){
	}
	~SCPI_Command_One_Param() {}
	void executeCMD(String stringArguments, String &error){
		cutCmdStr(stringArguments);
		parameter.parse(stringArguments);
		functionPointer(parameter);
	}
};

#endif