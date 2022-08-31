/**
 * @file Vector.h
 * @author Alexander Hammans (alex.hammans@gmail.com)
 * @brief A class to implement Vector to Arduino
 * @version 0.1
 * @date 2022-08-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef VECTOR_H
#define VECTOR_H
#include <Arduino.h>
#include "VectorIterator.h"


template <typename T>
class Vector
{
private:
	T * _values;
	T noValue;
	size_t _capacity;
	size_t _size;

	void makeCapacity(size_t count){
		if (_capacity <= count){
			this->reserve(count*1.28);
		}
	}

	void makeCapacity(){
		makeCapacity(_size);
	}

public:
	Vector(){
		_values = new T[1];
		_capacity = 1;
		_size = 0;
	}
	
	Vector(size_t newCap){
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

	// access specified element with bounds checking
	T & at(size_t index){
		if (index >= 0 && index < _size)
		{
			return _values[index];
		}
		return noValue;
	}
	
	// access specified element
	T & operator[](size_t index){
		return at(index);
	}

	// access the first element
	T & front(){
		return at(0);
	}

	// access the last element
	T & back(){
		return at(_size-1);
	}

	// direct access to the underlying array
	T * data(){
		return _values;
	}

	T* toArray(){
		T temp[_size];
		for (size_t i = 0; i < _size; i++)
		{
			temp[i] = at(i);
		}
		return temp;
	}

	// checks whether the container is empty
	bool empty() const{
		return _size == 0;
	}

	// returns the number of elements
	size_t size() const{
		return _size;
	}

	// reserves storage
	void reserve(size_t new_cap){
		T* newArr = new T[new_cap];
		_capacity = new_cap;
		for (size_t i = 0; i < _capacity; i++){
			newArr[i] = _values[i];
		}
		delete _values;
		_values = newArr;
	}

	// returns the number of elements that can be held in currently allocated storage
	size_t capacity(){
		return _capacity;
	}

	// reduces memory usage by freeing unused memory
	void shrink_to_fit(){
		if (_size*1.28 < _capacity){
			reserve(_size*1.28);
		}
	}

	// clears the contents
	void clear(){
		_size = 0;
	}

	// Inserts elements at the specified location in the container. inserts value before pos
	void insert( size_t pos, size_t count, const T& value ){
		makeCapacity(pos+count);
		makeCapacity(_size+count);
		T* temp = new T[_capacity];
		size_t tempPos;
		for (size_t i = 0; i < pos; i++)
		{
			temp[tempPos++] = _values[i];
		}
		for (size_t i = 0; i < count; i++)
		{
			temp[tempPos++] = value;
		}
		for (size_t i = pos; i < _size; i++)
		{
			temp[tempPos++] = _values[i];
		}
		_values = temp;
	}

	// erases elements
	void erase(size_t index){
		if (_size > index){
			for (size_t i=index; i<(_size-1); ++i){
				_values[i] = _values[i+1];
			}
			--_size;
		}
	}
	
	// adds an element to the end
	void push_back(const T & value){
		if ((_values != NULL)){
			makeCapacity(_size+1);
			_values[_size++] = value;
		}
	}

	/*
	void push_back(const T*& value, size_t count){
		if ((_values != NULL)){
			makeCapacity(_size+count);
			for (size_t i = 0; i < count; i++){
				_values[_size++] = value[i];
			}
		}
	}*/

	// removes the last element
	void pop_back(){
		if (_size > 0){
			--_size;
		}
	}

	// Resizes the container to contain count elements
	void resize( size_t count){
		makeCapacity(count);
		_size = count;
	}

	typedef VectorIterator<T> iterator;
	iterator begin(){
		return iterator(_values);
	}
	iterator end(){
		return iterator(_values,_size);
	}

	typedef VectorIterator<const T> const_iterator;
	const_iterator begin() const{
		return const_iterator(_values);
	}
	const_iterator end() const{
		return const_iterator(_values,_size);
	}
};
#endif
