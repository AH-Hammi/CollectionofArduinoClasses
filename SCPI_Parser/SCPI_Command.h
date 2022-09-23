#ifndef SCPI_COMMAND_H
#define SCPI_COMMAND_H

class SCPI_Command
{
private:
	String minKey = "";
	void extractMinKey(){
		int counter = 0;
		while (isUpperCase(key[counter])){
			minKey += key[counter];
			counter++;
		}
		if (key.indexOf("?")> 0){
			minKey += "?";
		}
	}
	void (*functionPointer) ();
public:
	const String key;
	SCPI_Command() : key("EMPTY"){
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
	virtual operator void * (){
	 	return functionPointer;
	} 
	String getKey(){
		return key;
	}
	String getMinKey(){
		return minKey;
	}
};
#endif
