#ifndef SCPI_COMMAND_NUMERIC_H
#define SCPI_COMMAND_NUMERIC_H

#include "SCPI_Command_Template.h"

template<class NT>
class SCPI_Command_Numeric : public SCPI_Command_Template<NT>
{
private:
	String prefixes[5][2] = {{"G","E9"},{"M","E6"},{"k","E3"},{"m","E-3"},{"u","e-6"}};
	String replacePrefixes(String arg){
		String retString = "";
		for (int i = 0; i < arg.length(); i++){
			for (int x = 0; x <= 5; x++){
				if (x == 5){
					retString.concat(arg[i]);
					break;
				}
				if (arg[i] == prefixes[x][0][0]){
					retString.concat(prefixes[x][1]);
					break;
				}
			}
		}
		return retString;
	}
	void cutCmdStr (String &cmdStr){
		if (cmdStr.indexOf(' ') == -1){
			cmdStr = "";
			return;
		}else{
			cmdStr = cmdStr.substring(cmdStr.indexOf(' '));
			cmdStr.trim();
		}
	}
	bool boundChecking = false;
	NT defaultValue = 0;
	NT minimumValue = 0;
	NT maximumValue = 0;
public:
	SCPI_Command_Numeric(const char* tempKey, void (*in)(NT)) :SCPI_Command_Template<NT>(String(tempKey),in){
	}
	SCPI_Command_Numeric( String tempKey, void (*in)(NT)) :SCPI_Command_Template<NT>(tempKey,in){
	}
	~SCPI_Command_Numeric() {}
	void setBounds(NT def, NT min, NT max){
		defaultValue = def;
		minimumValue = min;
		maximumValue = max;
		boundChecking = true;
	}
	virtual void executeCMD(String stringArguments, String &error){
		cutCmdStr(stringArguments);
		String lowerCaseArguments = stringArguments;
		lowerCaseArguments.toLowerCase();
		Serial.println(lowerCaseArguments);
		if (!boundChecking){
			functionPointer((NT)replacePrefixes(stringArguments).toDouble());
			return;
		}else{		
			if (lowerCaseArguments=="default"||lowerCaseArguments=="def"){
				functionPointer(defaultValue);
			}else if (lowerCaseArguments == "minimum"|| lowerCaseArguments == "min"){
				functionPointer(minimumValue);
			}else if (lowerCaseArguments == "maximum" || lowerCaseArguments == "max"){
				functionPointer(maximumValue);
			}else{
				double value = replacePrefixes(stringArguments).toDouble();
				Serial.println(value);
				if ((value >= minimumValue && value <= maximumValue)){
					delay(100);
					functionPointer((NT)value);
				}else if (value < minimumValue){
					Serial.println("Value below lower Bound");
				}else if (value>maximumValue){
					Serial.println("Value above upper Bound");
				}
			}
		}
	}
};

#endif
