#ifndef REGEXELEMENTS_H
#define REGEXELEMENTS_H

class RegexElement
{
public:
	RegexElement(){}
	~RegexElement(){}
	virtual bool match(String txt) = 0;
	//virtual char getFirstChar() = 0;
};

class RegexGroup : public RegexElement
{
private:
	String groupString;
public:
	RegexGroup():RegexElement() {}
	RegexGroup(String temp):RegexElement() {
		this->groupString = temp;
	}
	RegexGroup(char* temp):RegexElement() {
		this->groupString = String(temp);
	}
	RegexGroup(char temp):RegexElement() {
		this->groupString = String(temp);
	}
	~RegexGroup() {}
	bool match(String txt){
		if (sizeof(txt) != sizeof(groupString))
		{
			return false;
		}
		return txt.equals(groupString);
	}
	char getFirstChar(){
		return groupString[0];
	}
};

class RegexSet : public RegexElement
{
private:
	RegexGroup* possibleGroups;
	short numberOfGroups;
	bool notInverted = true;
public:
	RegexSet(){}
	
	RegexSet(String temp):RegexElement() {
		if (temp[0]=='^'){
			notInverted = false;
			RegexGroup tempRegexGroups[temp.length()-1];
			for (short i = 0; i < temp.length()-1 ; i++){
				tempRegexGroups[i] = RegexGroup(temp[i+1]);
			}
			this->possibleGroups = tempRegexGroups;
			this->numberOfGroups = temp.length()-1;
		}else{
			RegexGroup tempRegexGroups[temp.length()];
			for (short i = 0; i < temp.length() ; i++){
				tempRegexGroups[i] = RegexGroup(temp[i]);
			}
			this->possibleGroups = tempRegexGroups;
			this->numberOfGroups = temp.length();
		}
	}
	RegexSet(char* temp, short tempNumb, bool inverted = false):RegexElement() {
		RegexGroup tempRegexGroups[tempNumb];
		for (short i = 0; i < tempNumb ; i++){
			tempRegexGroups[i] = RegexGroup(temp[i]);
		}
		this->possibleGroups = tempRegexGroups;
		this->numberOfGroups = tempNumb;
		this->notInverted = !inverted;
	}
	RegexSet(RegexGroup* tempGroups, short tempNumb):RegexElement() {
		if (tempGroups[0].getFirstChar()=='^'){
			notInverted = false;
			RegexGroup temp[tempNumb-1];
			for (short i = 0; i < tempNumb-1; i++){
				temp[i] = tempGroups[i+1];
			}
			this->possibleGroups = temp;
			this->numberOfGroups = tempNumb-1;
		}else{
			this->possibleGroups = tempGroups;
			this->numberOfGroups = tempNumb;
		}
	}
	~RegexSet() {}

	bool match(String txt){
		for (short i = 0; i < numberOfGroups; i++)
		{
			if (possibleGroups[i].match(txt))
			{
				return notInverted;
			}
		}
		return notInverted;
	}
};

#endif