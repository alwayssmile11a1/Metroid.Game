#include "Array.h"



template<class T> Array<T>::Array()
{
}


template<class T> Array<T>::~Array()
{

}

template<class T> void Array<T>::Push(T element)
{
	vec.push_back(T);
}

template<class T> void Array<T>::Remove(T element)
{
	for (std::vector<T>::const_iterator it = vec.begin(); it != vec.end(); ++it)
	{
		if ((*it) == T)
		{
			vec.erase(it);
			break;
		}
	}
}

template<class T> T Array<T>::Remove(int index)
{
	T element = vec.erase(vec.begin() + index);
	return T;
}

template<class T> T  Array<T>::Get(int index)
{
	return vec.at(index);
}
