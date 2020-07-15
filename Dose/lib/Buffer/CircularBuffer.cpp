#include <CircularBuffer.h>



template<typename T>
CircularBuffer<T>::CircularBuffer(const size_t size)
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
T CircularBuffer<T>::get() const
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