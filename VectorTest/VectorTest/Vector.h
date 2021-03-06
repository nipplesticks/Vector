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

	void PushBack(const T & object);
	void PushBack(const Vector & other);
	void PushBack(const Vector & other, uint start, uint end);

	void PushFront(const T & object);
	void PushFront(const Vector & other);
	void PushFront(const Vector & other, uint start, uint end);

	void Insert(const T & object, uint at);


	T Pop();
	T Dequeue();
	T & Back();
	T & Front();
	T * Data();

	uint Size() const;
	bool IsEmpty() const;

	void SetIncrementialSize(uint incrementialSize);
	void ShrinkToFit();

	T & operator[](uint i) const;
	T & At(uint i) const;

	Vector & operator=(const Vector & other);

private:
	void _expand(uint increment);
	void _expandFront(uint increment);
	void _copy(const Vector & other);

private:
	void * m_data = nullptr;

	uint m_maxSize = 0;
	uint m_start = 0;
	uint m_end = 0;

	uint m_incrementialSize = 0;
	uint m_sizeOfObject = 0;
};

template<class T>
inline Vector<T>::Vector()
{
	m_sizeOfObject = sizeof(T);
	m_maxSize = 60;
	m_incrementialSize = 50;
	m_data = malloc(m_sizeOfObject * m_maxSize);
	m_start = 0;
	m_end = 0;
}

template<class T>
inline Vector<T>::Vector(uint initialSize)
{
	m_sizeOfObject = sizeof(T);
	m_maxSize = initialSize;
	m_incrementialSize = 50;
	m_data = malloc(m_sizeOfObject * initialSize);
	m_end = m_maxSize;
	m_start = 0;
	m_data = memset(m_data, 0, m_maxSize * m_sizeOfObject);
}

template<class T>
inline Vector<T>::Vector(uint initialSize, uint incrementialSize)
{
	m_sizeOfObject = sizeof(T);
	m_maxSize = initialSize;
	m_incrementialSize = incrementialSize;
	m_data = malloc(m_sizeOfObject * initialSize);
	m_end = m_maxSize;
	m_start = 0;
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
inline void Vector<T>::PushBack(const T & object)
{
	if (!(m_maxSize - m_end))
	{
		_expand(m_incrementialSize);
		m_incrementialSize *= 2;
	}

	memcpy((char*)m_data + m_end++ * m_sizeOfObject, &object, m_sizeOfObject);
}

template<class T>
inline void Vector<T>::PushBack(const Vector & other)
{
	uint delta = m_maxSize - m_end;
	uint oSize = other.Size();
	if (delta < oSize)
	{
		_expand((oSize - delta) + m_incrementialSize);
		m_incrementialSize *= 2;
	}

	memcpy((char*)m_data + m_end * m_sizeOfObject, (char*)other.m_data + other.m_start * other.m_sizeOfObject, oSize * other.m_sizeOfObject);

	m_end += other.m_end;
}

template<class T>
inline void Vector<T>::PushBack(const Vector & other, uint start, uint end)
{
	uint delta = m_maxSize - m_end;
	uint oSize = end - start;
	if (delta < oSize)
	{
		_expand((oSize - delta) + m_incrementialSize);
		m_incrementialSize *= 2;
	}

	memcpy((char*)m_data + m_end * m_sizeOfObject, (char*)other.m_data + (other.m_start + start) * other.m_sizeOfObject, oSize * other.m_sizeOfObject);

	m_end += other.m_end;
}

template<class T>
inline void Vector<T>::PushFront(const T & object)
{
	if (!m_start)
	{
		_expandFront(m_incrementialSize);
		m_incrementialSize *= 2;
	}

	memcpy((char*)m_data + --m_start * m_sizeOfObject, &object, m_sizeOfObject);
}

template<class T>
inline void Vector<T>::PushFront(const Vector & other)
{
	uint oSize = other.Size();
	if (m_start < oSize)
	{
		_expandFront((oSize - m_start) + m_incrementialSize);
		m_incrementialSize *= 2;
	}

	memcpy((char*)m_data + (m_start - oSize) * m_sizeOfObject, (char*)other.m_data + other.m_start * other.m_sizeOfObject, oSize * other.m_sizeOfObject);
	m_start -= oSize;
}

template<class T>
inline void Vector<T>::PushFront(const Vector & other, uint start, uint end)
{
	uint oSize = end - start;
	if (m_start < oSize)
	{
		_expandFront((oSize - m_start) + m_incrementialSize);
		m_incrementialSize *= 2;
	}

	memcpy((char*)m_data + (m_start - oSize) * m_sizeOfObject, (char*)other.m_data + (other.m_start + start) * other.m_sizeOfObject, oSize * other.m_sizeOfObject);
	m_start -= oSize;
}

template<class T>
inline void Vector<T>::Insert(const T & object, uint at)
{
	uint div = (m_end - m_start) / 2;
	if (at < div)
	{
		if (!m_start)
		{
			_expandFront(m_incrementialSize);
			m_incrementialSize *= 2;	
		}
		// Move data
		memcpy((char*)m_data + --m_start * m_sizeOfObject, (char*)m_data + (m_start + at) * m_sizeOfObject, (m_start + at) * m_sizeOfObject);

		memcpy((char*) m_data + (m_start + at) * m_sizeOfObject, &object, m_sizeOfObject)
	}
	else
	{

	}

}

template<class T>
inline T Vector<T>::Pop()
{
	T e = Back();

	m_end--;

	return e;
}

template<class T>
inline T Vector<T>::Dequeue()
{
	T e = Front();

	m_start++;

	return e;
}

template<class T>
inline T & Vector<T>::Back()
{
	return At(m_end - 1);
}

template<class T>
inline T & Vector<T>::Front()
{
	return At(0);
}

template<class T>
inline T * Vector<T>::Data()
{
	return (T*)(m_data + m_start * m_sizeOfObject);
}

template<class T>
inline uint Vector<T>::Size() const
{
	return m_end - m_start;
}

template<class T>
inline bool Vector<T>::IsEmpty() const
{
	return !(m_end - m_start);
}

template<class T>
inline void Vector<T>::SetIncrementialSize(uint incrementialSize)
{
	m_incrementialSize = incrementialSize;
}

template<class T>
inline void Vector<T>::ShrinkToFit()
{
	memcpy((char*)m_data, (char*)m_data + m_start * m_sizeOfObject, m_end * m_sizeOfObject);
	m_data = realloc((char*)m_data, m_end * m_sizeOfObject);
	m_end -= m_start;
	m_start = 0;
}

template<class T>
inline T & Vector<T>::operator[](uint i) const
{
	return *(T*)((char*)m_data + (m_start + i) * m_sizeOfObject);
}

template<class T>
inline T & Vector<T>::At(uint i) const
{
	return *(T*)((char*)m_data + (m_start + i) * m_sizeOfObject);
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
inline void Vector<T>::_expandFront(uint increment)
{
	m_maxSize += increment;
	m_data = realloc(m_data, m_maxSize * m_sizeOfObject);
	memcpy((char*)m_data + increment * m_sizeOfObject, (char*)m_data + m_start * m_sizeOfObject, (m_end - m_start) * m_sizeOfObject);
	m_start = increment;
	m_end += m_start;
}

template<class T>
inline void Vector<T>::_copy(const Vector & other)
{
	m_incrementialSize = other.m_incrementialSize;
	m_maxSize = other.m_maxSize;
	m_end = other.m_end;
	m_sizeOfObject = other.m_sizeOfObject;
	m_start = other.m_start;

	m_data = malloc(m_maxSize * m_sizeOfObject);
	memcpy(m_data, other.m_data, m_maxSize * m_sizeOfObject);
}
