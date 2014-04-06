/**************************************************************************************************
 * Title:         Array.hpp
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-21
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include <stdexcept>

namespace evansbros {

    template <typename T>
    Array<T>::Array(size_t size) : size(size)
    {
        if (size > 0) elements = new T[size];
    }

    template <typename T>
    Array<T>::Array(const Array<T> & other) : count(other.count), size(other.size)
    {
        if (size > 0) elements = new T[size];

        if (count > 0) {
            for (size_t i = 0; i < count; ++i) {
                elements[i] = other.elements[i];
            }
        }
    }

    template <typename T>
    Array<T>::Array(Array<T> && other) : count(other.count), size(other.size)
    {
        elements = other.elements;
        other.elements = nullptr;
    }

    template <typename T>
    Array<T>::~Array()
    {
        delete [] elements;
    }

    template <typename T>
    Index Array<T>::add(T element)
    {
        if (count == size) expand();

        elements[count] = element;
        return count++;
    }

    template <typename T>
    size_t Array<T>::deleteAll()
    {
        count = 0;
        return count;
    }

    template <typename T>
    size_t Array<T>::deleteLast()
    {
        if (count != 0) --count;
        return count;
    }

    template <typename T>
    size_t Array<T>::deleteLast(size_t n)
    {
        (n > count)? count = 0 : count -= n;
        return count;
    }

    template <typename T>
    size_t Array<T>::getCount() const
    {
        return count;
    }

    template <typename T>
    size_t Array<T>::getSize() const
    {
        return size;
    }

    template <typename T>
    T * Array<T>::getData() {
        return elements;
    }

    template <typename T>
    const T * Array<T>::getData() const {
        return elements;
    }

    template <typename T>
    T * Array<T>::begin()
    {
        return elements;
    }

    template <typename T>
    const T * Array<T>::begin() const
    {
        return elements;
    }

    template <typename T>
    const T * Array<T>::cbegin() const
    {
        return elements;
    }

    template <typename T>
    T * Array<T>::end()
    {
        return elements + count;
    }

    template <typename T>
    const T * Array<T>::end() const
    {
        return elements + count;
    }


    template <typename T>
    const T * Array<T>::cend() const
    {
        return elements + count;
    }

    template <typename T>
    T & Array<T>::operator[](size_t position)
    {
        if (!(position < count)) throw std::out_of_range("position must be less than count");

        return elements[position];
    }
    
    template <typename T>
    const T & Array<T>::operator[](size_t position) const
    {
        if (!(position < count)) throw std::out_of_range("position must be less than count");
        
        return elements[position];
    }

    template <typename T>
    void Array<T>::expand()
    {
        if (size == maximumSize) throw std::length_error("This array is already the maximumSize");

        size_t new_size;

        if (size == 0) {
            new_size = 1;
        } else if (size < maximumSize / 1024) {
            new_size = 2 * size;
        } else if (size < maximumSize - maximumSize / 1024) {
            new_size = size + maximumSize / 1024;
        } else {
            new_size = maximumSize;
        }

        T *temp = new T[new_size];
        for (size_t i = 0; i < count; ++i) {
            temp[i] = elements[i];
        }

        delete [] elements;

        size = new_size;
        elements = temp;
    }

}