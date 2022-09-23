/**
 * @file EEPROM_Value.h
 * @author Alexander Hammans (a.hammans@kostal.com)
 * @brief Simple Class to Work with a value in EEPROM
 * @version 0.1
 * @date 2022-08-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef EEPROM_VALUE_H
#define EEPROM_VALUE_H

#include <EEPROM.h>

template<class T>
class EEPROM_Value
{
private:
	T value;
	int eepromAdress = 0;
public:
	EEPROM_Value() {}
	EEPROM_Value(int eepromAdress) {
		this->eepromAdress = eepromAdress;
		EEPROM.get(eepromAdress,this->value);
	}
	~EEPROM_Value() {}
	T get(){
		return value;
	}
	void set(T newVal){
		if (eepromAdress != 0)
		{
			EEPROM.put(eepromAdress,newVal);
			this->value = newVal;
		}
	}
	EEPROM_Value& operator= (T val){
		set(val);
		return *this;
	}
	operator T() const{
		return get();
	}
};

#endif
