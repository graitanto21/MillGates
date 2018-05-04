
//By GiacomoNasi
#ifndef EXP_VECTOR
#define EXP_VECTOR

#include <vector>
#include <string>
#include <iostream>
#define INIT_SIZE 1

template <class T> class ExpVector{

private:

	int _logicSize, _realSize;
	std::vector<T> _wrapped;

	void goDouble(){
		_realSize *= 2;
		_wrapped.resize(_realSize);
	}

	bool goHalf(){
		if (_realSize%2 != 0)
			return false;
		_realSize /= 2;
		_wrapped.resize(_realSize);
		return true;
	}

public:

	ExpVector(){
		_logicSize = 0;
		_realSize = INIT_SIZE;
		_wrapped.resize(_realSize);
	}

	ExpVector(int realSize){
		_logicSize = 0;
		this -> _realSize = realSize;
		_wrapped.resize(realSize);
	}

	~ExpVector(){
	}

	//WORK WITH THE VECTOR

	void add(T toAdd){
		if(_logicSize == _realSize)
			goDouble();
		_wrapped[_logicSize] = toAdd;
		_logicSize ++;
	}

	void erase(int index){
		//TODO inefficient implementation
		_wrapped.erase(_wrapped.begin() + index);
		_logicSize --;
		if(_logicSize == _realSize/2)
			goHalf();
	}

	T get(int index){
		return _wrapped[index];
	}

	void set(int index, T value){
		_wrapped[index] = value;
	}

	//OUTPUT
	void print(){
		for (int i=0; i<_logicSize; i++){
			std::cout << _wrapped[i] << " ";
		}
		std::cout << "\nLOGIC: " << _logicSize << "\n";
		std::cout << "REAL: "<< _realSize << "\n";
		std::cout << "REAL: "<< _wrapped.size() << "\n\n";

	}

	//GETTERS
	int getLogicSize(){
		return _logicSize;
	}

	int getRealSize(){
		return _realSize;
	}
};

#endif

