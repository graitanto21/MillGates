
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

	virtual void add(T toAdd);
	virtual void erase(int index);

	virtual T get(int index);
	virtual void set(int index, T value);

	virtual int getLogicSize();
	virtual int getRealSize();

	virtual void print();

	virtual ~ExpVector();
};

#endif
