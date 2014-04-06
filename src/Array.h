/**************************************************************************************************
 * Title:         Array.h
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-21
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "numerical_types.h"

namespace evansbros {

    template <typename T>
    class Array {
    public:

        /**
         * Constructs an empty Array.
         */
        Array() = default;

        /**
         * Constructs an Array with the given size.
         * @param size_t the initial size of this Array
         */
        Array(size_t size);

        /**
         * Copy constructor
         */
        Array(const Array<T> & other);

        /**
         * Move constructor
         */
        Array(Array<T> && other);

        /**
         * Destructor
         */
        ~Array();

        /**
         * Adds an element to this Array, expanding it if necessary.
         * @param  element the element to add to this Array
         * @return the element's index in this Array
         * @see    deleteAll
         * @see    deleteLast
         * @see    expand
         */
        Index add(T element);

        /**
         * Deletes all the elements in this Array.
         * @return the number of elements remaining in this Array (zero is always returned)
         * @see    add
         * @see    deleteLast
         */
        size_t deleteAll();

        /**
         * Deletes the last element of this Array.
         * @return the number of elements remaining in this Array
         * @see    add
         * @see    deleteAll
         */
        size_t deleteLast();

        /**
         * Deletes the last n elements of this Array.
         * If there are fewer than n elements, all of them are deleted.
         * @param  n the number of elements to delete
         * @return the number of elements remaining in this Array
         * @see    add
         * @see    deleteAll
         */
        size_t deleteLast(size_t n);

        /**
         * @return the number of elements in this Array
         * @see getSize
         * @see getData();
         */
        size_t getCount() const;

        /**
         * @return the size of this Array
         * @see getCount
         */
        size_t getSize() const;


        /**
         * @return a pointer to the Array data
         * @see getCount()
         */
        T * getData();

        /**
         * @return a pointer to the Array data (const)
         * @see getCount()
         */
        const T * getData() const;

        /**
         * @return an iterator to the begining of this Array
         */
        T * begin();

        /**
         * @return an iterator to the begining of this Array (const)
         */
        const T * begin() const;

        /**
         * @return an iterator to the begining of this Array (const)
         */
        const T * cbegin() const;

        /**
         * @return an iterator to the end of this Array
         */
        T * end();

        /**
         * @return an iterator to the end of this Array (const)
         */
        const T * end() const;

        /**
         * @return an iterator to the end of this Array (const)
         */
        const T * cend() const;

        /**
         * Subscript operator for this Array
         */
        T & operator[](size_t position);

        /**
         * Subscript operator for this Array (const)
         */
        const T & operator[](size_t position) const;

    private:
        /**
         * Expands this array
         * @throws std::length_error if the array is already the maximumSize
         */
        void expand();

        size_t count = 0;
        size_t size  = 0;
        T *elements =  nullptr;
    };

}

#include "Array.hpp"