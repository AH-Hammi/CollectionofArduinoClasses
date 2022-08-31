#ifndef KEYVALUEPAIRS_H
#define KEYVALUEPAIRS_H

#include <Arduino.h>
#include "Vector/Vector.h"


template<class Key,class T> struct KeyValuePair{
	Key _key;
	T _value;
};

// A class with a Key and a Value that return the Value according to the Key.
template<class Key,class T> class KeyValuePairs{
private:
	Vector<KeyValuePair<Key,T>> _pairs;
public:
	KeyValuePairs(){
	}

	KeyValuePairs(KeyValuePair<Key,T>* pairs, size_t count){
		for (size_t i = 0; i < count; i++){
			_pairs.push_back(pairs[i]);
		}
	}

	~KeyValuePairs(){
		
	}
	
	// Returns the value associated with the key.
	T at(Key key){
		for (int i = 0; i < _pairs.size(); i++)
		{
			if (_pairs[i].key == key){
				return _pairs[i].value;
			}
		}
	}
	
	// Returns the value associated with the key.
	T operator[](Key key){
		return at(key);
	}

	// Adds a new element
	void add(Key key, T value){
		KeyValuePair<Key,T> newPair;
		newPair.key = key;
		newPair.value = value;
		_pairs.push_back(newPair);
	}
};

#endif