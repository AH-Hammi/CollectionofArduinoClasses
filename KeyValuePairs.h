#ifndef KEYVALUEPAIRS_H
#define KEYVALUEPAIRS_H

// A class with a Key and a Value that return the Value according to the Key.
template<class Key,class T> class KeyValuePairs{
private:
	Key* _keys;
	T* _values;
	size_t _capacity;
	size_t _size;
	
	void makeCapacity(size_t count){
		if (_capacity <= count){
			this->reserve(count*1.28);
		}
	}
	
	void makeCapacity(){
		makeCapacity(_capacity);
	}
	
public:
	KeyValuePairs(){
		_keys = NULL;
		_values = NULL;
		_capacity = 0;
		_size = 0;
	}
	
	KeyValuePairs(size_t newCap){
		reserve(newCap);
	}
	
	// Replaces the contents with count copies of value
	void assign( size_t count, const T& value ){
		
		if (_size < count){
			_size = count;
		}
		for (size_t i = 0; i < count; i++){
			this->_values[i] = value;
		}
	}
	
	// Returns the number of elements in the KeyValuePairs.
	size_t size(){
		return _size;
	}
	
	// Returns the number of elements that the KeyValuePairs can hold without resizing.
	size_t capacity(){
		return _capacity;
	}
	
	// Returns true if the KeyValuePairs is empty.
	bool empty(){
		return _size == 0;
	}
	
	// Returns true if the KeyValuePairs is full.
	bool full(){
		return _size == _capacity;
	}
	
	// Reserves storage for at least n elements.
	void reserve(size_t n){
		if (_capacity < n){
			Key* newKeys = new Key[n];
			T* newValues = new T[n];
			for (size_t i = 0; i < _size; i++){
				newKeys[i] = _keys[i];
				newValues[i] = _values[i];
			}
			delete[] _keys;
			delete[] _values;
			_keys = newKeys;
			_values = newValues;
			_capacity = n;
		}
	}
	
	// Removes all elements from the KeyValuePairs.
	void clear(){
		_size = 0;
	}
	
	// Returns the value associated with the key.
	T at(Key key){
		for (size_t i = 0; i < _size; i++){
			if (_keys[i] == key){
				return _values[i];
			}
		}
		return T();
	}
	
	// Returns the value associated with the key.
	T operator[](Key key){
		return at(key);
	}

	// Adds a new element
	void add(Key key, T value){
		makeCapacity();
		_keys[_size] = key;
		_values[_size] = value;
		_size++;
	}
};

#endif