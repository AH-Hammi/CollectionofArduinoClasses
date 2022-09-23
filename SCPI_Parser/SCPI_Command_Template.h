#ifndef SCPI_COMMAND_TEMPLATE_H
#define SCPI_COMMAND_TEMPLATE_H

#include "SCPI_Command.h"

template <typename NT>
class SCPI_Command_Template : public SCPI_Command
{
protected:
	void (*functionPointer) (NT);
public:
	SCPI_Command_Template() :SCPI_Command("EMPTY"){
	}
	SCPI_Command_Template(String tempKey, void (*in)(NT)) :SCPI_Command(tempKey){
		functionPointer = in;
	}
	~SCPI_Command_Template() {}
	virtual void executeCMD(String stringArguments, String &error){
		return;
	}
	operator void*(){
		return functionPointer;
	} 
};

#endif