#ifndef SCPI_PARAMETER_H
#define SCPI_PARAMETER_H

#include <string.h>
#include <stdlib.h>

class SCPI_Parameter
{
private:
	enum Type {StringType, IntType, DoubleType, BoolType} type;
	union typeValue{
		const char* string;
		int integer;
		double floating;
		bool boolean;
	} value;
	
	template<class T>
	struct bounds{
		bool hasBounds = false;
		T min;
		T max;
		T def;
	};
	bounds<int> intBounds;
	bounds<double> doubleBounds;

	String prefixes[5][2] = {{"G","E9"},{"M","E6"},{"k","E3"},{"m","E-3"},{"u","e-6"}};
	double convertPrefix(String arg){
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
		return retString.toDouble();
	}
public:
	SCPI_Parameter(){
		type = StringType;
		value.string = 0;
	}
	SCPI_Parameter(String in = String(" ")){
		type = StringType;
		value.string = in.c_str();
	}
	SCPI_Parameter(int in = 0){
		type = IntType;
		value.integer = in;
	}
	SCPI_Parameter(double in = 0.0){
		type = DoubleType;
		value.floating = in;
	}
	SCPI_Parameter(bool in = false){
		type = BoolType;
		value.boolean = in;
	}
	SCPI_Parameter(const SCPI_Parameter& other){
		type = other.type;
		switch (type) {
		case StringType:
			value.string = other.value.string;
			break;
		case IntType:
			value.integer = other.value.integer;
			break;
		case DoubleType:
			value.floating = other.value.floating;
			break;
		case BoolType:
			value.boolean = other.value.boolean;
			break;
		}
	}
	SCPI_Parameter& operator=(const SCPI_Parameter& other){
		type = other.type;
		switch (type) {
		case StringType:
			value.string = other.value.string;
			break;
		case IntType:
			value.integer = other.value.integer;
			break;
		case DoubleType:
			value.floating = other.value.floating;
			break;
		case BoolType:
			value.boolean = other.value.boolean;
			break;
		}
		return *this;
	}
	void clear(){
		type = IntType;
		value.string = 0;
	}
	void parse(String str){
		switch (type)
		{
		case StringType:
			value.string = str.c_str();
			break;
		case IntType:
			value.integer = (int)convertPrefix(str);
			break;
		case DoubleType:
			value.floating = convertPrefix(str);
			break;
		case BoolType:
			if (str.equalsIgnoreCase("ON")|| str.equalsIgnoreCase("1")|| str.equalsIgnoreCase("TRUE")|| str.equalsIgnoreCase("YES")){
				value.boolean = true;
			}else{
				value.boolean = false;
			}
			break;
		default:
			break;
		}
	}
	void setBounds(int min, int max, int def){
		intBounds.hasBounds = true;
		intBounds.min = min;
		intBounds.max = max;
		intBounds.def = def;
	}
	void setBounds(double min, double max, double def){
		doubleBounds.hasBounds = true;
		doubleBounds.min = min;
		doubleBounds.max = max;
		doubleBounds.def = def;
	}
	SCPI_Parameter& operator=(String value){
		type = StringType;
		this->value.string = value.c_str();
		return *this;
	}
	SCPI_Parameter& operator=(const char* value){
		type = StringType;
		this->value.string = value;
		return *this;
	}
	SCPI_Parameter& operator=(int value){
		type = IntType;
		this->value.integer = value;
		return *this;
	}
	SCPI_Parameter& operator=(double value){
		type = DoubleType;
		this->value.floating = value;
		return *this;
	}
	SCPI_Parameter& operator=(bool value){
		type = BoolType;
		this->value.boolean = value;
		return *this;
	}
	bool operator==(const char* value) const{
		if (type != StringType) return false;
		return strcmp(this->value.string, value) == 0;
	}
	bool operator==(int value) const{
		if (type != IntType) return false;
		return this->value.integer == value;
	}
	bool operator==(double value) const{
		if (type != DoubleType) return false;
	}
	bool operator==(bool value) const{
		if (type != BoolType) return false;
		return this->value.boolean == value;
	}
	operator int() const{
		if (type != IntType) return 0;
		return value.integer;
	}
	operator double() const{
		if (type != DoubleType) return 0;
		return value.floating;
	}
	operator bool() const{
		if (type != BoolType) return false;
		return value.boolean;
	}
	operator String() const{
		if (type != StringType) return "";
		return String(value.string);
	}

	static void splitParameterString(const String &str, String *arg, int &argCount){
		// Split the string into arguments
		// Check if the string contains high commas
		int highCommaCount = 0;
		for (int i = 0; i < str.length(); i++){
			if (str[i] == '"') highCommaCount++;
		}
		if (highCommaCount % 2 != 0){
			// If the number of high commas is odd, then the string should be splited along spaces
			argCount = 0;
			String tmp = "";
			for (int i = 0; i < str.length(); i++){
				if (str[i] == ' '){
					arg[argCount] = tmp;
					tmp = "";
					argCount++;
				}else{
					tmp += str[i];
				}
			}
			arg[argCount] = tmp;
			argCount++;
			return;
		}else{
			// If the number of high commas is even, split the string along high commas
			argCount = 0;
			String tmp = "";
			bool inHighComma = false;
			for (int i = 0; i < str.length(); i++){
				if (str[i] == '"'){
					inHighComma = !inHighComma;
				}else if (str[i] == ' ' && !inHighComma){
					arg[argCount] = tmp;
					tmp = "";
					argCount++;
				}else{
					tmp += str[i];
				}
			}
			arg[argCount] = tmp;
			argCount++;
			return;
		}
	}
};

#endif // SCPI_PARAMETER_H
