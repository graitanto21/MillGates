
//By GiacomoNasi
#ifndef EXP_VECTOR
#define EXP_VECTOR

#include <vector>
#include <string>
#include <iostream>
#define INIT_SIZE 1

template <class T> class ExpVector{

private:

	int logicSize, realSize;
	std::vector<T> wrapped;

	void goDouble(){
		realSize *= 2;
		wrapped.resize(realSize);
	}

	bool goHalf(){
		if (realSize%2 != 0)
			return false;
		realSize /= 2;
		wrapped.resize(realSize);
		return true;
	}

public:

	ExpVector(){
		logicSize = 0;
		realSize = INIT_SIZE;
		wrapped.resize(realSize);
	}

	ExpVector(int realSize){
		logicSize = 0;
		this -> realSize = realSize;
		wrapped.resize(realSize);
	}

	~ExpVector(){}

	//WORK WITH THE VECTOR

	void add(T toAdd){
		if(logicSize == realSize)
			goDouble();
		wrapped[logicSize] = toAdd;
		logicSize ++;
	}

	void erase(int index){
		//TODO inefficient implementation
		wrapped.erase(wrapped.begin() + index);
		logicSize --;
		if(logicSize == realSize/2)
			goHalf();
	}

	T get(int index){
		return wrapped[index];
	}

	void set(int index, T value){
		wrapped[index] = value;
	}

	//OUTPUT
	void print(){
		for (int i=0; i<logicSize; i++){
			std::cout << wrapped[i] << " ";
		}
		std::cout << "\nLOGIC: " << logicSize << "\n";
		std::cout << "REAL: "<< realSize << "\n";
		std::cout << "REAL: "<< wrapped.size() << "\n\n";

	}

	//GETTERS
	int getLogicSize(){
		return logicSize;
	}

	int getRealSize(){
		return realSize;
	}
};

#endif

