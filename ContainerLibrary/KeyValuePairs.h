/**
 * @file KeyValuePairs.h
 * @author Alexander Hammans (alex.hammans@gmail.com)
 * @brief A Class like the map class from C++ STL for Arduino
 * @version 0.1
 * @date 2022-09-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef KEYVALUEPAIRS_H
#define KEYVALUEPAIRS_H

#include "Vector.h"


template<class Key,class NT> class KeyValuePair{
	public:
		Key key;
		NT value;
		KeyValuePair(){
		}
		KeyValuePair(Key key, NT value){
			this->key = key;
			this->value = value;
		}
		~KeyValuePair(){}
};

// A class with a Key and a Value that return the Value according to the Key.
template<class Key,class NT> class KeyValuePairs{
private:
	Vector<KeyValuePair<Key,NT>> _pairs;
public:
	KeyValuePairs(){
	}

	KeyValuePairs(KeyValuePair<Key,NT>* pairs, size_t count){
		for (size_t i = 0; i < count; i++){
			_pairs.push_back(pairs[i]);
		}
	}

	~KeyValuePairs(){
		
	}
	
	// Returns the value associated with the key.
	NT at(Key key){
		for (int i = 0; i < _pairs.size(); i++)
		{
			if (_pairs[i].key == key){
				return _pairs[i].value;
			}
		}
	}
	
	// Returns the value associated with the key.
	NT operator[](Key key){
		return at(key);
	}

	// Returns the value associated with the index
	NT at(size_t index){
		return _pairs[index].value;
	}

	// Returns the value associated with the index
	NT operator[](size_t index){
		return at(index);
	}

	//Check if list is Emtpy
	bool isEmpty(){
		return _pairs.isEmpty();
	}

	// Returns the number of elements in the list.
	int size(){
		return _pairs.size();
	}

	// Clear the contentes of the KeyValuePairs
	void clear(){
		_pairs.clear();
	}

	// Add a new KeyValuePair to the list.
	void add(Key key, NT value){
		_pairs.push_back(KeyValuePair<Key,NT>(key, value));
	}

	// Adds all the elements of Another Key Value Pairs to this list.
	void addAll(KeyValuePairs<Key,NT>& another){
		for (int i = 0; i < another.size(); i++){
			_pairs.push_back(another._pairs[i]);
		}
	}

	// Insert a new KeyValuePair to the list.
	void insert(Key key, NT value, int index){
		_pairs.insert(KeyValuePair<Key,NT>(key, value), index);
	}

	//inserts an element or assigns to the current element if the key already exists 
	void insertOrAssign(Key key, NT value){
		for (int i = 0; i < _pairs.size(); i++)
		{
			if (_pairs[i].key == key){
				_pairs[i].value = value;
				return;
			}
		}
		_pairs.push_back(KeyValuePair<Key,NT>(key, value));
	} 

	// Erases Elements from the KeyValuePairs
	void erase(int index){
		_pairs.erase(index);
	}

	// Erases Elements from the KeyValuePairs
	void erase(Key key){
		_pairs.erase(getIndex(key));
	}

	// returns the number of elements matching specific key 
	int count(Key key){
		int count = 0;
		for (int i = 0; i < _pairs.size(); i++)
		{
			if (_pairs[i].key == key){
				count++;
			}
		}
		return count;
	}

	//finds element with specific key 
	KeyValuePair<Key,NT>* find(Key key){
		for (int i = 0; i < _pairs.size(); i++)
		{
			if (_pairs[i].key == key){
				return &_pairs[i];
			}
		}
		return NULL;
	}

	// Check if Key is in the list
	bool contains(Key key){
		return getIndex(key) != -1;
	}

	//Returns a Pointer to the array with the KeyValuePairs
	KeyValuePair<Key,NT>* getPairs(){
		return _pairs.data();
	}

	// Returns one Pair from the list.
	KeyValuePair<Key,NT>* getPair(int index){
		return &_pairs[index];
	}

	//Get Index of Key
	int getIndex(Key key){
		for (int i = 0; i < _pairs.size(); i++)
		{
			if (_pairs[i].key == key){
				return i;
			}
		}
		return -1;
	}

	//Remove Element according to Key
	void remove(Key key){
		int index = getIndex(key);
		if (index != -1){
			remove(index);
		}
	}
};

#endif