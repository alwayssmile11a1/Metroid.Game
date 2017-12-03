#ifndef ARRAY_H
#define ARRAY_H
#include<vector>

//deprecated class
template<class T> class Array
{
private:
	std::vector<T> vec; //temporary
	
public:
	Array();
	~Array();

	void Push(T element);
	void Remove(T element);
	T Remove(int index);
	T Get(int index);

};


#endif //
