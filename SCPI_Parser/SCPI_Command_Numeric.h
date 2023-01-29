/**
 * @file SCPI_Command_Numeric.h
 * @author Alexander Hammans (a.hammans@kostal.com)
 * @brief This file contains the definition of the SCPI_Command_Numeric class.
 * @version 1.0
 * @date 20.12.2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SCPI_COMMAND_NUMERIC_H
#define SCPI_COMMAND_NUMERIC_H

#include "SCPI_Command.h"

/**
 * @brief This class represents a single SCPI command of type numeric
 * This class handles the execution of a command with a numeric parameter.
 * It is a child class of SCPI_Command.
 * It translates the string parameter to a numeric value and executes the function with the numeric value.
 * It supports SI prefixes. As well as . and , as decimal separators.
 * @tparam T 
 */
template<class T>
class SCPI_Command_Numeric : public SCPI_Command
{
private:
	/**
	 * @brief List of all supported SI prefixes
	 * Giga:	G = 10^9
	 * Mega:	M = 10^6
	 * Kilo:	k = 10^3
	 * Milli:	m = 10^-3
	 * Micro:	u = 10^-6
	 */
	const String prefixes[5][2] = {{"G","E9"},{"M","E6"},{"k","E3"},{"m","E-3"},{"u","e-6"}};

	/**
	 * @brief Replaces the SI prefix with the corresponding exponent
	 * 
	 * @param arg 
	 * @return String 
	 */
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

	/**
	 * @brief Internal method, cuts away 
	 * 
	 * @param cmdStr 
	 */
	void cutCmdStr (String &cmdStr){
		cmdStr = cmdStr.substring(cmdStr.indexOf(' '));
		cmdStr.trim();
	}
	bool boundChecking = false;
	T defaultValue = 0;
	T minimumValue = 0;
	T maximumValue = 0;
public:
	/**
	 * @brief Pointer to the function that should be executed
	 * 
	 */
	void (*functionPointer) (T);
	SCPI_Command_Numeric(char* tempKey, void (*in)(T)) :SCPI_Command(String(tempKey)) {
		functionPointer = in;
	}
	SCPI_Command_Numeric( String tempKey, void (*in)(T)) :SCPI_Command(tempKey) {
		functionPointer = in;
	}
	~SCPI_Command_Numeric() {}
	/**
	 * @brief Sets the bounds for the command
	 * This method sets the bounds for the value and enables bound checking.
	 * @param def Default Value
	 * @param min Minimum Value
	 * @param max Maximum Value
	 */
	void setBounds(T def, T min, T max){
		defaultValue = def;
		minimumValue = min;
		maximumValue = max;
		boundChecking = true;
	}

	/**
	 * @brief Executes the command
	 * This method executes the command with the given parameter.
	 * It first converts the parameter to a numeric value and then executes the function.
	 * @param stringArguments 
	 * @param error 
	 */
	void executeCMD(String stringArguments, String &error){
		cutCmdStr(stringArguments);
		String lowerCaseArguments = stringArguments;
		lowerCaseArguments.toLowerCase();
		double value = replacePrefixes(stringArguments).toDouble();
		if(!boundChecking){
			functionPointer(value);
		} else {
			if (lowerCaseArguments=="default"||lowerCaseArguments=="def"){
			functionPointer(defaultValue);
			} else if (lowerCaseArguments == "minimum"|| lowerCaseArguments == "min"){
				functionPointer(minimumValue);
			} else if (lowerCaseArguments == "maximum" || lowerCaseArguments == "max"){
				functionPointer(maximumValue);
			} else {
				if (value < minimumValue){
					Serial.println("Value below lower Bound, setting to minimum");
					functionPointer(minimumValue);
				} else if (value>maximumValue){
					Serial.println("Value above upper Bound, setting to maximum");
					functionPointer(maximumValue);
				} else {
					functionPointer(value);
				}
			}
		}
		
	}
};

#endif
