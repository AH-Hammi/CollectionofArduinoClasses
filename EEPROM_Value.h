/**
 * @file EEPROM_Value.h
 * @author Alexander Hammans (a.hammans@kostal.com)
 * @brief Simple Class to Work with a value in EEPROM
 * @version 1.0
 * @date 20.12.2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef EEPROM_VALUE_H
#define EEPROM_VALUE_H

#include <EEPROM.h>

/**
 * @brief Simple Class to Work with a value in EEPROM
 * This Class is a simple wrapper for a value in EEPROM. It can be used to store a value in EEPROM and read it back.
 * @tparam T The Type of the value to store in EEPROM
 */
template<class T>
class EEPROM_Value
{
private:
	T value;
	int eepromAddress = 0;
public:
	/**
	 * @brief Construct a new eeprom value object
	 * This constructor should not be used. Only for initialization.
	 */
	EEPROM_Value() {}

	/**
	 * @brief Construct a new eeprom value object
	 * The value will be read from EEPROM and stored in the object.
	 * @param eepromAddress The Address in EEPROM to store the value
	 */
	EEPROM_Value(int eepromAddress) {
		this->eepromAddress = eepromAddress;
		EEPROM.get(eepromAddress,this->value);
	}
	~EEPROM_Value() {}

	/**
	 * @brief Get the value
	 * This method returns the value stored in the object.
	 * @return T The value
	 */
	T get(){
		return value;
	}

	/**
	 * @brief Set the value
	 * This method sets the value stored in the object and writes it to EEPROM.
	 * This method does nothing if the eepromAddress is 0.
	 * @param newVal The new value
	 */
	void set(T newVal){
		if (eepromAddress != 0)
		{
			EEPROM.put(eepromAddress,newVal);
			this->value = newVal;
		}
	}
	
	/**
	 * @brief Set the Value
	 * This method calls the set method.
	 * @param val 
	 * @return EEPROM_Value& 
	 */
	EEPROM_Value& operator= (T val){
		set(val);
		return *this;
	}

	/**
	 * @brief Get the value
	 * This method calls the get method.
	 * @return value
	 */
	operator T() const{
		return get();
	}
};

#endif
