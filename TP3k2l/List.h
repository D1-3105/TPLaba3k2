#pragma once

template<class T>
class List {
private:
	T* list;
	size_t length;
public:
	List(): length(0) {
		list = new T[0];
	};
	void push_back(T object);
	T pop();
	T operator[](size_t pos);
	T* to_array();
	size_t getLength();
};

template<class T>
inline void List<T>::push_back(T object)
{
	T* new_list = new T[length + 1];
	for (int i = 0; i < length; i++) {
		new_list[i] = list[i];
	}
	new_list[length] = object;
	delete[] list;
	list = new_list;
	length++;
}

template<class T>
inline T List<T>::pop()
{
	T* new_list = new T[length-1];
	T last = list[length-1];
	for (int i = 0; i < length - 1; i++) {
		new_list[i] = list[i];
	}
	delete[] list;
	list = new_list;
	length--;
	return last;
}

template<class T>
inline T List<T>::operator[](size_t pos)
{
	return list[pos];
}

template<class T>
inline T* List<T>::to_array()
{
	return list;
}

template<class T>
inline size_t List<T>::getLength()
{
	return length;
}
