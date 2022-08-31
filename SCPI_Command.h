#ifndef SCPI_COMMAND_H
#define SCPI_COMMAND_H

class SCPI_Command
{
private:
	void (*functionPointer) ();
	String minKey = "";
	void extractMinKey(){
		int counter = 0;
		while (isUpperCase(key[counter]))
		{
			minKey += key[counter];
			counter++;
		}
		if (key.indexOf("?")> 0)
		{
			minKey += "?";
		}
		
	}
public:
	const String key;
	SCPI_Command() : key("EMPTY"){
	}
	SCPI_Command(String tempKey) : key(tempKey){
		extractMinKey();
	}
	SCPI_Command(void (*in)(), String tempKey) : key(tempKey) {
		functionPointer = in;
		extractMinKey();
	}
	~SCPI_Command() {}
	bool isKey(String cmdStr){
		return (cmdStr.equalsIgnoreCase(minKey) || cmdStr.equalsIgnoreCase(key));
	}
	virtual void executeCMD(String stringArguments, String &error){
		functionPointer();
	}
};
#endif