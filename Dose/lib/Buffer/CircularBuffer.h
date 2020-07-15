/**
 * @file CircularBuffer.h
 * @author koray ilbuga (koray0199@gmail.com)
 * @brief Non thread-safe static circular buffer implementation.
 * @version 0.1
 * @date 2020-07-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _CircularBuffer_
#define _CircularBuffer_

#include <stdint.h>
/*
namespace std
{
    template<typename T>
    struct is_nullptr
    {
      static const bool value =  (T == decltype(nullptr));
    };
}
*/
namespace
{
    using size_t  = __SIZE_TYPE__;
}

//TODO- handle copy constructor and assignment
template<typename T>
class CircularBuffer
{
    //static_assert(std::is_nullptr<T>::value, "Error: Type parameter is nullptr");

    public:
    explicit CircularBuffer(size_t size);
    void put(const T& data);
    T get();
    void flush();
    bool isFull() const;
    bool isEmpty() const;
    size_t capacity() const;
    size_t size() const;
    ~CircularBuffer();


    private:
    CircularBuffer();
    
    const size_t max_elements;
    T* buffer;
    size_t head;
    size_t tail;
    bool full;
    
    
};



template<typename T>
CircularBuffer<T>::CircularBuffer(size_t size)
:max_elements{size}, full{false}, buffer{new T[max_elements]}, head{0}, tail{0}
{

}

template<typename T>
void CircularBuffer<T>::flush()
{
    head = tail;

}

template<typename T>
bool CircularBuffer<T>::isEmpty() const
{
    return (!full && (head == tail));
}

template<typename T>
bool CircularBuffer<T>::isFull() const
{
    return full;
}

template<typename T>
size_t CircularBuffer<T>::capacity() const
{
    return max_elements;
}

template<typename T>
size_t CircularBuffer<T>::size() const
{
	size_t size = max_elements;

	if(!full)
	{
		if(head >= tail)
		{
			size = head - tail;
		}
		else
		{
			size = max_elements + head - tail;
		}
	}

	return size;
}

template<typename T>
void CircularBuffer<T>::put(const T& item)
{
	buffer[head] = item;

	if(full)
	{
		tail = (tail + 1) % max_elements;
	}

	head = (head + 1) % max_elements;

	full = head == tail;
}

template<typename T>
T CircularBuffer<T>::get()
{
	if(isEmpty())
	{
		return T();
	}


	auto val = buffer[tail];
	full = false;
	tail = (tail + 1) % max_elements;

	return val;
}

template<typename T>
CircularBuffer<T>::~CircularBuffer()
{
	delete buffer;
}

#endif