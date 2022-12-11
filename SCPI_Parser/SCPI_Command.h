#ifndef SCPI_COMMAND_H
#define SCPI_COMMAND_H

class SCPI_Command
{
private:
	String minKey = "";

	// fills in minKey with the minimum key, containing only upper case letters, colons and a question mark
	// Example:	RESistance:OUTput? => RES:OUT? 
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
public:
	void (*functionPointer) ();
	const String key;
	SCPI_Command() : key("EMPTY"){
	}
	SCPI_Command(const char* tempKey) : key(tempKey){
		extractMinKey();
	}
	SCPI_Command(String tempKey) : key(tempKey){
		extractMinKey();
	}
	SCPI_Command(String tempKey, void (*in)()) : SCPI_Command(tempKey){
		functionPointer = in;
	}
	~SCPI_Command() {}
	bool isKey(String cmdStr){
		return (cmdStr.equalsIgnoreCase(minKey) || cmdStr.equalsIgnoreCase(key));
	}
	virtual void executeCMD(String stringArguments, String &error){
		functionPointer();
	}
	String getKey(){
		return key;
	}
	String getMinKey(){
		return minKey;
	}
};
#endif
