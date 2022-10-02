#ifndef ARRAY_H
#define ARRAY_H


// A class to implement Array to Arduino, with some features of std::array
template <typename T, int SIZE>
class Array
{
private:
	T _values[SIZE];

public:
	Array(){
	}

	// access specified element with bounds checking
	T & at(int index){
		if (index >= 0 && index < SIZE)
		{
			return _values[index];
		}
	}

	// access specified element
	T & operator[](int index){
		return at(index);
	}

	// access the first element
	T & front(){
		return _values[0];
	}

	// access the last element
	T & back(){
		return _values[SIZE-1];
	}

	// Returns a pointer to the first element of the array
	T* data(){
		return _values;
	}

	// Returns the number of elements in the array
	int size(){
		return SIZE;
	}

	// Clears the array
	void clear(){
		forEach([](T& elem){
			elem = T();
		});
	}

	// Erases one element of the Array
	void erase(int index){
		at(index) = T();
	}

	// fill the container with specified value
	void fill(const T& value){
		for (int i = 0; i < SIZE; i++)
		{
			_values[i] = value;
		}
	}

	// swaps the contents
	void swap(Array<T, SIZE> & other){
		T temp;
		for (int i = 0; i < SIZE; i++)
		{
			temp = _values[i];
			_values[i] = other._values[i];
			other._values[i] = temp;
		}
	}

	// Executes the function for each element in the array
	void forEach(void (*func)(T&)){
		for (int i = 0; i < SIZE; i++)
		{
			func(_values[i]);
		}
	}

	// Executes the function for each element in the array and finds the first element that matches the condition
	T find(bool (*func)(T&)){
		for (int i = 0; i < SIZE; i++)
		{
			if (func(_values[i]))
			{
				return _values[i];
			}
		}
		return T();
	}

	// Executes the function for each element in the array and finds all elements that match the condition
	Array<T, SIZE> findAll(bool (*func)(T&)){
		Array<T, SIZE> temp;
		int j = 0;
		for (int i = 0; i < SIZE; i++)
		{
			if (func(_values[i]))
			{
				temp[j] = _values[i];
				j++;
			}
		}
		return temp;
	}
};
#endif