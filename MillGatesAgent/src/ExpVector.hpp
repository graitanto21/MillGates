//By GiacomoNasi

#include "ExpVector.h"
#include <iostream>
#include <string>
#include "stdio.h"


//CONSTRUCTORS AND DESTRRUCTORS
template <class T>
ExpVector<T>::ExpVector(){
	logicSize = 0;
	realSize = INIT_SIZE;
	wrapped.resize(realSize);
}

template <class T>
ExpVector<T>::ExpVector(int realSize){
	logicSize = 0;
	this -> realSize = realSize;
	wrapped.resize(realSize);
}

template <class T>
ExpVector<T>::~ExpVector(){}

//WORK WITH THE VECTOR
template <class T>
void ExpVector<T>::goDouble(){
	realSize *= 2;
	wrapped.resize(realSize);
}

template <class T>
bool ExpVector<T>::goHalf(){
	if (realSize%2 != 0)
		return false;
	realSize /= 2;
	wrapped.resize(realSize);
	return true;
}

template <class T>
void ExpVector<T>::add(T toAdd){
	if(logicSize == realSize)
		goDouble();
	wrapped[logicSize] = toAdd;
	logicSize ++;
}

template <class T>
void ExpVector<T>::erase(int index){
	//TODO inefficient implementation
	wrapped.erase(wrapped.begin() + index);
	logicSize --;
	if(logicSize == realSize/2)
		goHalf();
}

template <class T>
T ExpVector<T>::get(int index){
	return wrapped[index];
}

template <class T>
void ExpVector<T>::set(int index, T value){
	wrapped[index] = value;
}

template <class T>
void ExpVector<T>::swap(T valA, T valB){
	std::swap(valA, valB);
}

//OUTPUT
template <class T>
void ExpVector<T>::print(){
	for (int i=0; i<logicSize; i++){
		std::cout << wrapped[i] << " ";
	}
	std::cout << "\nLOGIC: " << logicSize << "\n";
	std::cout << "REAL: "<< realSize << "\n";
	std::cout << "REAL: "<< wrapped.size() << "\n\n";

}

//GETTERS
template <class T>
int ExpVector<T>::getLogicSize(){
	return logicSize;
}

template <class T>
int ExpVector<T>::getRealSize(){
	return realSize;
}

/*int main(int argc, char **argv) {
	ExpVector<int> v(3);
	for(int i=0; i<20; i++){
		v.add(i+1);
		v.print();
	}
	for(int i=0; i<20; i++){
		v.erase(0);
		v.print();
	}
}*/
