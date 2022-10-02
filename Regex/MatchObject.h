/*
	Match Object
	A Match Object is an object containing information about the search and the result.
*/

class MatchObject
{
private:
	int positions[2];
	
public:
	// .string returns the string passed into the function
	const String string;

	MatchObject(String tempTxt, int tempStart, int tempEnd) : string(tempTxt) {
		this->positions[0] = tempStart;
		this->positions[1] = tempEnd;
	}
	~MatchObject() {}

	// Return the starting position of the match
	int start(){
		return positions[0];
	}

	// Return the ending position of the match
	int end(){
		return positions[1];
	}

	// Return a tuple containing the (start, end) positions of the match
	int* span (){
		return positions;
	}

	// Return the string matched by the RE
	String group(){
		return string.substring(positions[0],positions[1]);
	}

};