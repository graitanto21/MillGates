#ifndef EXP_VECTOR
#define EXP_VECTOR

#include <vector>
#include <string>
#define INIT_SIZE 1

template <class T> class ExpVector{

private:
	int logicSize, realSize;

	void resize();

public:

	std::vector<T> wrapped;

	ExpVector();
	ExpVector(int realSize);
	void add(T toAdd);
	~ExpVector();
	T get(int index);
	void set(int index, T value);

	void print();

};

#endif
