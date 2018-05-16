//By GiacomoNasi
#ifndef EXP_VECTOR
#define EXP_VECTOR

#include <vector>
#include <string>
#define INIT_SIZE 1

template <class T> class ExpVector{

private:

	int logicSize, realSize;
	std::vector<T> wrapped;

	void goDouble();
	bool goHalf();

public:



	ExpVector();
	ExpVector(int realSize);
	~ExpVector();

	void add(T toAdd);
	void erase(int index);

	T get(int index);
	void set(int index, T value);

	int getLogicSize();
	int getRealSize();

	void swap(T valA, T valB);
	void print();

};

#include "ExpVector.hpp"

#endif
