#ifndef SCPI_COMMAND_NUMERIC_H
#define SCPI_COMMAND_NUMERIC_H

#include "SCPI_Command.h"

template<class T>
class SCPI_Command_Numeric : public SCPI_Command
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
		cmdStr = cmdStr.substring(cmdStr.indexOf(' '));
		cmdStr.trim();
	}
	bool noBoundChecking = true;
	T defaultValue = 0;
	T minimumValue = 0;
	T maximumValue = 0;
public:
	void (*functionPointer) (T);
	SCPI_Command_Numeric(char* tempKey, void (*in)(T)) :SCPI_Command(String(tempKey)) {
		functionPointer = in;
		noBoundChecking = true;
	}
	SCPI_Command_Numeric( String tempKey, void (*in)(T)) :SCPI_Command(tempKey) {
		functionPointer = in;
		noBoundChecking = true;
	}
	~SCPI_Command_Numeric() {}
	void setBounds(T def, T min, T max){
		defaultValue = def;
		minimumValue = min;
		maximumValue = max;
		noBoundChecking = false;
	}
	void executeCMD(String stringArguments, String &error){
		cutCmdStr(stringArguments);
		String lowerCaseArguments = stringArguments;
		lowerCaseArguments.toLowerCase();
		if (lowerCaseArguments=="default"||lowerCaseArguments=="def"){
			functionPointer(defaultValue);
		}else if (lowerCaseArguments == "minimum"|| lowerCaseArguments == "min"){
			functionPointer(minimumValue);
		}else if (lowerCaseArguments == "maximum" || lowerCaseArguments == "max"){
			functionPointer(maximumValue);
		}else{
			float value = replacePrefixes(stringArguments).toFloat();
			if (noBoundChecking||(value >= minimumValue && value <= maximumValue)){
				functionPointer(value);
			}else if (value < minimumValue){
				Serial.println("Value below lower Bound");
			}else if (value>maximumValue){
				Serial.println("Value above upper Bound");
			}
		}
	}
};

#endif
