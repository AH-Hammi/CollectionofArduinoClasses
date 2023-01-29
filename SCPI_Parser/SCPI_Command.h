/**
 * @file SCPI_Command.h
 * @author Alexander Hammans (a.hammans@kostal.com)
 * @brief This file contains the SCPI_Command class
 * @version 1.0
 * @date 20.12.2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SCPI_COMMAND_H
#define SCPI_COMMAND_H

#ifdef DEBUG
	#define dprint(x) Serial.print(x)
	#define dprintln(x) Serial.println(x) 
#else
	#define dprint(x)
	#define dprintln(x)
#endif

/**
 * @brief This class represents a single SCPI command
 * 
 */
class SCPI_Command
{
private:
	String minKey = "";
	/**
	 * @brief Internal method, to extract the minimum key
	 * The minimum key is the key without any lower case letters.
	 * Example: RESistance:OUTput? => RES:OUT?
	 * 
	 */
	void extractMinKey(){
		int counter = 0;
		int temp = 0;
		// add a star to minKey if there is one
		if (key[0] == '*'){
			minKey += "*";
			counter++;
		}
		do{
			// add all upper case letters to minKey
			while (isUpperCase(key[counter])){
				minKey += key[counter];
				counter++;
			}
			// add a colon to minKey if there is one
			temp = key.indexOf(":",counter);
			if (temp > 0){
				minKey += ":";
				counter = temp+1;
			}
		} while (temp > 0); // repeat until there is no colon left
		// add a question mark to minKey if there is one
		if (key.indexOf("?")> 0){
			minKey += "?";
		}
	}
protected:
	String cutCMDString(String cmdStr){
		dprintln("Cut CMD String: "+cmdStr);
		dprintln("Cut String: "+cmdStr.substring(cmdStr.indexOf(" ")+1));
		return cmdStr.substring(cmdStr.indexOf(" ")+1);
	}
public:
	/**
	 * @brief Pointer to the function that should be executed when the command is called
	 * 
	 */
	void (*functionPointer) ();

	/**
	 * @brief The key of the command
	 * 
	 */
	const String key;

	/**
	 * @brief Construct a new SCPI_Command object
	 * 
	 */
	SCPI_Command() : key("EMPTY"){
	}
	
	/**
	 * @brief Construct a new SCPI_Command object
	 * This constructor takes a key and a function pointer as arguments.
	 * Furthermore it automatically extracts the minimum key.
	 * @param tempKey 
	 */
	SCPI_Command(String tempKey) : key(tempKey){
		extractMinKey();
	}

	/**
	 * @brief Construct a new SCPI_Command object
	 * This constructor takes a key and a function pointer as arguments.
	 * Furthermore it automatically extracts the minimum key.
	 * @param tempKey 
	 * @param tempFunctionPointer 
	 */
	SCPI_Command(String tempKey, void (*in)()) : SCPI_Command(tempKey){
		functionPointer = in;
	}

	~SCPI_Command() {}

	/**
	 * @brief Check if the given key matches the command key
	 * 
	 * @param cmdStr 
	 * @return true if the key matches
	 */
	bool isKey(String cmdStr){
		return (cmdStr.equalsIgnoreCase(minKey) || cmdStr.equalsIgnoreCase(key));
	}

	/**
	 * @brief Execute the command
	 * This method executes the command by calling the function pointer.
	 * @param stringArguments 
	 * @param error 
	 */
	virtual void executeCMD(String stringArguments, String &error){
		functionPointer();
	}

	/**
	 * @brief Print out the keys of the command
	 * 
	 */
	void printKeys(){
		Serial.println("Keys are:");
		Serial.println(key);
		Serial.println(minKey);
	}

	/**
	 * @brief Get the Key object
	 * 
	 * @return String 
	 */
	String getKey(){
		return key;
	}

	/**
	 * @brief Get the Min Key object
	 * 
	 * @return String 
	 */
	String getMinKey(){
		return minKey;
	}
};
#endif
