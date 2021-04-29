#ifndef ARRAY_H
#define ARRAY_H
#include <cstdlib>

template <typename T>
class dynamic_array
{
private:
    size_t len, cap;
    T* data;
public:
    dynamic_array(size_t len);
    dynamic_array();
    ~dynamic_array();
    dynamic_array(const dynamic_array<T>& arr);
    const dynamic_array<T>& operator=(const dynamic_array<T>& arr);
    void copy(const dynamic_array<T>& arr);
    void push(T element);
    void pop();
    inline size_t get_length() const { return len; }
    inline size_t get_capacity() const { return cap; }
    inline T& operator[](size_t i) { return data[i]; }
    inline T* get() const;
    static dynamic_array<T> from_array(T* array, size_t size);
    size_t allocated() const { return len * sizeof(T); }
};

template <typename T>
inline dynamic_array<T>::dynamic_array(size_t len)
{
	this->len = len;
    this->cap = len + 1;
	this->data = new T[len + 1];
}

template <typename T>
inline dynamic_array<T>::dynamic_array()
{
    this->cap = 1;
	this->len = 0;
	this->data = new T[1];
}

template <typename T>
inline dynamic_array<T>::~dynamic_array()
{
    delete[] data;
}

template <typename T>
inline dynamic_array<T>::dynamic_array(const dynamic_array<T>& arr)
{
    this->copy(arr);
}

template <typename T>
const dynamic_array<T>& dynamic_array<T>::operator=(const dynamic_array<T>& arr)
{
    this->copy(arr);
    return *this;
}

template <typename T>
inline void dynamic_array<T>::copy(const dynamic_array<T>& arr)
{
    this->len = 0;
    this->cap = 1;
    this->data = new T[arr.get_capacity()];
    for(size_t i = 0; i < arr.get_length(); i++)
    {
        this->push(arr.get()[i]);
    }
}

template <typename T>
inline void dynamic_array<T>::push(T element)
{
    if (len == cap)
    {
		T* temp = new T[2 * cap];
 
        // copying old array elements to new array
        for (size_t i = 0; i < cap; i++)
        {
			temp[i] = data[i];
        }
 
        // deleting previous array
        delete[] data;
        this->cap *= 2;
        this->data = temp;
	}
 
    // Inserting data
    this->data[len] = element;
    this->len++;
}

template <typename T>
inline void dynamic_array<T>::pop()
{
    this->len--;
}

template <typename T>
inline T* dynamic_array<T>::get() const
{
    return data;
}

template <typename T>
dynamic_array<T> dynamic_array<T>::from_array(T* array, size_t size)
{
    dynamic_array<T> arr;
    for(size_t i = 0; i < size; i++)
    {
        arr.push(array[i]);
    }
    return arr;
}

#endif