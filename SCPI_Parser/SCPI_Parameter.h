/**
 * @file SCPI_Parameter.h
 * @author Alexander Hammans (a.hammans@kostal.com)
 * @brief This file contains the SCPI_Parameter class
 * @version 0.1
 * @date 22.12.2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SCPI_PARAMETER_H
#define SCPI_PARAMETER_H

#ifdef DEBUG
	#define dprint(x) Serial.print(x)
	#define dprintln(x) Serial.println(x) 
#else
	#define dprint(x)
	#define dprintln(x)
#endif

template <byte NumberOfParameters>
class SCPI_Parameter{
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

	String parameters[NumberOfParameters];

	double minimumValue[NumberOfParameters] = {0.0};
	double maximumValue[NumberOfParameters] = {0.0};
	double defaultValue[NumberOfParameters] = {0.0};
	bool boundChecking[NumberOfParameters] = {false};

public:
	SCPI_Parameter(){}
	SCPI_Parameter(String paraString){
		setParameters(paraString);
	}
	~SCPI_Parameter(){}

	// Interpret the command string and extract the parameters
	// The parameters are separated by a space
	// A String parameter can be enclosed in double quotes
	// A String parameter can contain a space
	void setParameters(String paraString){
		dprintln("setParameters");
		dprintln("paraString: " + paraString);
		byte paraNumber = 0;
		String parameter = "";
		bool inString = false;
		for (int i = 0; i < paraString.length() ; i++) {
			char c = paraString.charAt(i);
			if (c == ' ' && !inString) {
				if (paraNumber+1 >= NumberOfParameters) {
					break;
				}
				if (parameter.length() > 0) {
					parameters[paraNumber] = parameter;
					paraNumber++;
					parameter = "";
				}
			} else if (c == '"') {
				inString = !inString;
			} else {
				parameter += c;
			}
		}
		if (parameter.length() > 0) {
			parameters[paraNumber] = parameter;
		}
		// Fill out remaining parameters with empty strings
		for (int i = paraNumber+1; i < NumberOfParameters; i++) {
			parameters[i] = "";
		}	
		for (int i = 0; i < NumberOfParameters; i++) {
			dprintln("parameters[" + String(i) + "]: " + parameters[i]);
		}
	}

	// -------------------------------------------------------------------- Numeric Interpretation
	/**
	 * @brief Sets the bounds for the command
	 * This method sets the bounds for the value and enables bound checking.
	 * @param parameterNumber Number of the parameter
	 * @param def Default Value
	 * @param min Minimum Value
	 * @param max Maximum Value
	 */
	void setBounds(byte parameterNumber, double def, double min, double max){
		defaultValue[parameterNumber] = def;
		minimumValue[parameterNumber] = min;
		maximumValue[parameterNumber] = max;
		boundChecking[parameterNumber] = true;
	}

	// Return one parameter from the command interpreted as a numeric value
	double getDouble(byte parameterNumber){
		String lowerCaseArguments = parameters[parameterNumber];
		lowerCaseArguments.toLowerCase();
		double value = replacePrefixes(lowerCaseArguments).toDouble();
		if(!boundChecking[parameterNumber]){
			return value;
		} else {
			if (lowerCaseArguments=="default"||lowerCaseArguments=="def"){
				return defaultValue[parameterNumber];
			} else if (lowerCaseArguments == "minimum"|| lowerCaseArguments == "min"){
				return minimumValue[parameterNumber];
			} else if (lowerCaseArguments == "maximum" || lowerCaseArguments == "max"){
				return maximumValue[parameterNumber];
			} else {
				if (value < minimumValue[parameterNumber]){
					Serial.println("Value below lower Bound, setting to minimum");
					return minimumValue[parameterNumber];
				} else if (value>maximumValue[parameterNumber]){
					Serial.println("Value above upper Bound, setting to maximum");
					return maximumValue[parameterNumber];
				} else {
					return value;
				}
			}
		}
	}

	int getInt(byte parameterNumber){
		return (int)getDouble(parameterNumber);
	}

	float getFloat(byte parameterNumber){
		return (float)getDouble(parameterNumber);
	}

	long getLong(byte parameterNumber){
		return (long)getDouble(parameterNumber);
	}

	// -------------------------------------------------------------------- String Interpretation
	String getString(byte parameterNumber){
		return parameters[parameterNumber];
	}

	// -------------------------------------------------------------------- Boolean Interpretation
	bool getBool(byte parameterNumber){
		String lowerCaseArguments = parameters[parameterNumber];
		lowerCaseArguments.toLowerCase();
		if (lowerCaseArguments == "on" || lowerCaseArguments == "1" || lowerCaseArguments == "true"){
			return true;
		} else if (lowerCaseArguments == "off" || lowerCaseArguments == "0" || lowerCaseArguments == "false"){
			return false;
		} else {
			return false;
		}
	}
};

#endif // SCPI_PARAMETER_H
