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
    explicit CircularBuffer(const size_t size);
    void put(const T& data);
    T get() const;
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

#endif