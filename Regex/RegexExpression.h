#ifndef REGEXEXPRESSION_H
#define REGEXEXPRESSION_H

#include "RegexElements.h"

class RegexExpression
{
private:
	RegexElement* elements;
	short numberOfElements;
public:
	RegexExpression(){}
	RegexExpression(String temp) {

	}
	RegexExpression(RegexSet* tempSets, short tempNumb) {
		
	}
	~RegexExpression(){}
	bool match(String txt){
		
	}
};

#endif