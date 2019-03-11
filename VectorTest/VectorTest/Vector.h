#pragma once
#include <cstdlib>
#include <cstring>

#define uint unsigned int

template <class T>
class Vector
{
public:
	Vector();
	Vector(uint initialSize);
	Vector(uint initialSize, uint incrementialSize);
	Vector(const Vector & other);

	~Vector();

	void Push(const T & object);
	void Push(const Vector & other);
	T Pop();
	T & Back();
	T & Front();
	T * Data();

	uint Size();
	bool IsEmpty();
	void SetIncrementialSize(uint incrementialSize);

	T & operator[](uint i);
	T & At(uint i);

	Vector & operator=(const Vector & other);

private:
	void _expand(uint increment);
	void _copy(const Vector & other);

private:
	void * m_data = nullptr;

	uint m_size = 0;
	uint m_maxSize = 0;
	uint m_incrementialSize = 0;

	uint m_sizeOfObject = 0;
};

template<class T>
inline Vector<T>::Vector()
{
	m_sizeOfObject = sizeof(T);
	m_maxSize = 50;
	m_incrementialSize = 50;
	m_data = malloc(m_sizeOfObject * m_maxSize);
	m_size = 0;
}

template<class T>
inline Vector<T>::Vector(uint initialSize)
{
	m_sizeOfObject = sizeof(T);
	m_maxSize = initialSize;
	m_incrementialSize = 50;
	m_data = malloc(m_sizeOfObject * initialSize);
	m_size = m_maxSize;
	m_data = memset(m_data, 0, m_maxSize * m_sizeOfObject);
}

template<class T>
inline Vector<T>::Vector(uint initialSize, uint incrementialSize)
{
	m_sizeOfObject = sizeof(T);
	m_maxSize = initialSize;
	m_incrementialSize = incrementialSize;
	m_data = malloc(m_sizeOfObject * initialSize);
	m_size = m_maxSize;
	m_data = memset(m_data, 0, m_maxSize * m_sizeOfObject);
}

template<class T>
inline Vector<T>::Vector(const Vector & other)
{
	_copy(other);
}

template<class T>
inline Vector<T>::~Vector()
{
	free(m_data);
}

template<class T>
inline void Vector<T>::Push(const T & object)
{
	if (!(m_maxSize - m_size))
	{
		_expand(m_incrementialSize);
		m_incrementialSize *= 2;
	}

	memcpy((char*)m_data + m_size++ * m_sizeOfObject, &object, m_sizeOfObject);


	//*(T*)((char*)m_data + m_size++ * m_sizeOfObject) = object;
}

template<class T>
inline void Vector<T>::Push(const Vector & other)
{
	uint delta = m_maxSize - m_size;
	if (delta < other.m_size)
	{
		_expand((other.m_size - delta) + m_incrementialSize);
		m_incrementialSize *= 2;
	}

	m_data = memcpy((char*)m_data + m_size * m_sizeOfObject, other.m_data, other.m_size * other.m_sizeOfObject);

	m_size += other.m_size;
}

template<class T>
inline T Vector<T>::Pop()
{
	T e = Back();

	m_size--;

	return e;
}

template<class T>
inline T & Vector<T>::Back()
{
	return At(m_size - 1);
}

template<class T>
inline T & Vector<T>::Front()
{
	return At(0);
}

template<class T>
inline T * Vector<T>::Data()
{
	return (T*)m_data;
}

template<class T>
inline uint Vector<T>::Size()
{
	return m_size;
}

template<class T>
inline bool Vector<T>::IsEmpty()
{
	return !m_size;
}

template<class T>
inline void Vector<T>::SetIncrementialSize(uint incrementialSize)
{
	m_incrementialSize = incrementialSize;
}

template<class T>
inline T & Vector<T>::operator[](uint i)
{
	return *(T*)((char*)m_data + i * m_sizeOfObject);
}

template<class T>
inline T & Vector<T>::At(uint i)
{
	return *(T*)((char*)m_data + i * m_sizeOfObject);
}

template<class T>
inline Vector<T> & Vector<T>::operator=(const Vector & other)
{
	if (this != &other)
	{
		free(m_data);
		_copy(other);
	}

	return *this;
}

template<class T>
inline void Vector<T>::_expand(uint increment)
{
	m_maxSize += increment;
	m_data = realloc(m_data, m_maxSize * m_sizeOfObject);
}

template<class T>
inline void Vector<T>::_copy(const Vector & other)
{
	m_incrementialSize = other.m_incrementialSize;
	m_maxSize = other.m_maxSize;
	m_size = other.m_size;
	m_sizeOfObject = other.m_sizeOfObject;

	m_data = malloc(m_size * m_sizeOfObject);
	m_data = memcpy(m_data, other.m_data, m_size * m_sizeOfObject);
}
