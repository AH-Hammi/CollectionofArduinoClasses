/*
	Define Regex Patterns like
	String pattern = R"(pattern)"
	Metacharacters
	Metacharacters are characters with a special meaning:
	Character	Description 																	Example
	[] 			A set of characters 															"[a-m]"
	\ 			Signals a special sequence (can also be used to escape special characters) 		"\d"
	. 			Any character (except newline character) 										"he..o"
	^ 			Starts with 																	"^hello"
	$ 			Ends with 																		"planet$"
	* 			Zero or more occurrences 														"he.*o"
	+ 			One or more occurrences 														"he.+o"
	? 			Zero or one occurrences 														"he.?o"
	{m}			Exactly m number of occurrences													"he.{2}o"
	{m,n}		Between m and n number of occurrences 											"he.{1,2}o"
	| 			Either or 																		"falls|stays"
	() 			Capture and group

	Special Sequences
	A special sequence is a \ followed by one of the characters in the list below, and has a special meaning:
	Character 	Description 																	Example
	\A 			Returns a match if the specified characters are at the beginning of the string 	"\AThe"
	\b 			Returns a match where the specified characters are at the beginning or at the end of a word
																								"\bain"
	\B 			Returns a match where the specified characters are present, but NOT at the beginning (or at the end) of a word
																								"\Bain"
	\d			Matches any decimal digit; this is equivalent to the class [0-9].
	\D			Matches any non-digit character; this is equivalent to the class [^0-9].
	\s			Matches any whitespace character; this is equivalent to the class [ \t\n\r\f\v].
	\S			Matches any non-whitespace character; this is equivalent to the class [^ \t\n\r\f\v].
	\w			Matches any alphanumeric character; this is equivalent to the class [a-zA-Z0-9_].
	\W			Matches any non-alphanumeric character; this is equivalent to the class [^a-zA-Z0-9_].

	\Z 			Returns a match if the specified characters are at the end of the string 		"Spain\Z"

	

	Sets
	A set is a set of characters inside a pair of square brackets [] with a special meaning:
	Set 		Description
	[arn] 		Returns a match where one of the specified characters (a, r, or n) is present
	[a-n] 		Returns a match for any lower case character, alphabetically between a and n
	[^arn] 		Returns a match for any character EXCEPT a, r, and n
	[0123] 		Returns a match where any of the specified digits (0, 1, 2, or 3) are present
	[0-9] 		Returns a match for any digit between 0 and 9
	[0-5][0-9] 	Returns a match for any two-digit numbers from 00 and 59
	[a-zA-Z] 	Returns a match for any character alphabetically between a and z, lower case OR upper case
	[+] 		In sets, +, *, ., |, (), $,{} has no special meaning, so [+] means: return a match for any + character in the string
*/

#include "MatchObject.h"
#include "RegexElements.h"
#include "RegexExpression.h"
#include "../ContainerLibrary/Vector.h"
#include "../ContainerLibrary/KeyValuePairs.h"

class Regex
{
private:
	KeyValuePairs<char,RegexSet> escapeCharacters= {
		{'d',RegexSet("0123456789",10)},
		{'D',RegexSet("0123456789",10,true)},
		{'s',RegexSet(" \t\n\r\f\v",6)},
		{'S',RegexSet(" \t\n\r\f\v",6,true)},
		{'w',RegexSet("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_",62)},
		{'W',RegexSet("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_",62,true)},
		{'\\',RegexSet("\\",1)},
		{'^',RegexSet("^",1)},
		{'$',RegexSet("$",1)},
		{'*',RegexSet("*",1)},
		{'+',RegexSet("+",1)},
		{'?',RegexSet("?",1)},
		{'{',RegexSet("{",1)},
		{'}',RegexSet("}",1)},
		{'[',RegexSet("[",1)},
		{']',RegexSet("]",1)},
		{'(',RegexSet("(",1)},
		{')',RegexSet(")",1)},
		{'|',RegexSet("|",1)},
		{'.',RegexSet(".",1)},
		{'A',RegexSet("^",1)},
		{'Z',RegexSet("$",1)}
	};
	RegexGroup* convertToGroups(String expression){
		Vector<RegexSet> tempVec;
		short iter = 0;
		while (iter<expression.length()){
			if (expression[iter]=='\\'){
				iter++;
				tempVec.push_back(escapeCharacters.at(expression[iter]));
			}else if (expression[iter]=='['){
				iter++;
				String tempStr;
				while (expression[iter]!=']'){
					tempStr+=expression[iter];
					iter++;
				}
				tempVec.push_back(RegexSet(tempStr));
			}else{
				tempVec.push_back(RegexSet(expression[iter]));
			}
			iter++;
		}
	}
public:
	Regex() {
	}
	~Regex() {}

	// Matching

	// Determine if the RE matches at the beginning of the string.
	static MatchObject match(RegexExpression expression, String txt){
		expression.match(txt);
	}

	// Scan through a string, looking for any location where this RE matches.
	static MatchObject search(String expression, String txt){

	}
	
	// The findall() function returns a list containing all matches.
	// The list contains the matches in the order they are found.
	// If no matches are found, an empty list is returned:
	static MatchObject* findall(String expression, String txt){

	}

	// Modifying Strings

	// Split the string into a list, splitting it wherever the RE matches
	// You can control the number of occurrences by specifying the maxsplit parameter: -1 is no limit
	static String* split(String expression, String txt, int maxsplit){

	}

	// Find all substrings where the RE matches, and replace them with a different string
	// You can control the number of replacements by specifying the count parameter: -1 is no limit 
	static String sub(String expression, String replacement, String txt, int count){

	}
};
