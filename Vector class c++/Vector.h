#pragma once


#include<iostream>
using namespace std;

// vector iterator

template <typename Vector>
class VectorIterator
{

public:
    using ValueType = typename Vector::ValueType;  // assign one type into another
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;

private:
    PointerType m_ptr;  // this pointertype is template of vector class and 

public:

    // this construtor needs to take a pointer basically in starting where he point
    VectorIterator(PointerType ptr)
        :m_ptr(ptr) // pointing to first element of vector buffer
    {

    }

    VectorIterator& operator++()
    {
        m_ptr++;

        return *this;
    }

    VectorIterator operator++(int)
    {
        VectorIterator iterator = *this;
        ++(*this);
        return iterator;
    }


    VectorIterator& operator--()
    {
        m_ptr--;

        return *this;
    }

    VectorIterator operator--(int)
    {
        VectorIterator iterator = *this;
        --(*this);
        return iterator;
    }

    ReferenceType operator[](int index)
    {
        return *(m_ptr[index]); //deference it
    }

    PointerType operator->()
    {
        return m_ptr;
    }

    ReferenceType operator*()
    {
        return *(m_ptr);
    }

    bool operator==(const VectorIterator& other) const
    {
        return m_ptr == other.m_ptr; // compare one pointer with otherS
    }

    bool operator!=(const VectorIterator& other) const
    {
        return !(*this == other); // deference it and compare
    }

};



template<typename T>
class Vector
{
public: 
    using ValueType = T;
    using Iterator = VectorIterator<Vector<T>>; // its enable feature like vector<int>::Iterator  like std lib


private:
    T* m_Data = nullptr;
    size_t m_size = 0;
    size_t m_capacity = 0;

private:

    void Re_alloc(size_t newCapacity)
    {

        // reallocate new memeory if buffer full


        T* newBlock = new T[newCapacity];

        if (newCapacity < m_size)
            m_size = newCapacity;

        // assign


        for (size_t i = 0; i < m_size; i++)
            newBlock[i] = std::move(m_Data[i]); // instead of copy again and again we move data if we work with raw pointer

        delete[] m_Data;
        m_Data = newBlock;

        m_capacity = newCapacity;


    }


public:
    Vector()
    {
        Re_alloc(2);
    }

    ~Vector()
    {
        delete[] m_Data;
    }

    // Iterator

    Iterator begin()
    {
        return Iterator(m_Data);   // this take class member pointer and return new vectorIterator here with m_data pointer 
    }

    Iterator end()
    {
        return Iterator(m_Data + m_size);   // return last element of new vector iterator 
    }



    size_t Size() const
    {
        return m_size;
    }


    void PopBack()
    {
        if (m_size > 0)
        {
            m_Data[m_size--].~T();
              // --> explicility call destructor and remove the resource and nullipy the object;
        }
    }

    void Clear()
    {
        for (size_t i = 0; i < m_size; i++)
        {
            //instead of m_size--;
            //we call destructor here
            m_Data[i].~T();

          
        }

        m_size = 0;
    }

    void push_back(const T& value)
    {
        if (m_size >= m_capacity)
        {
            Re_alloc(m_capacity + m_capacity / 2);
        }

        m_Data[m_size] = value;
        m_size++;
    }


    const T& operator[](size_t index) const
    {
        if (index >= m_size)
        {
            cout << " Out of Bound - Range does not exist " << endl;
        }
        return m_Data[index];
    }

    T& operator[](size_t index)  // non const version in case we use modifier 
    {
        if (index >= m_size)
        {
            cout << " Out of Bound - Range does not exist " << endl;
        }
        return m_Data[index];
    }


    void printVector(const Vector<T>& vector)
    {
        for (size_t i = 0; i < vector.Size(); i++)
        {
            cout << vector[i] << " ";
        }
    }

    T& VectorSum(const Vector<T>& vec)
    {
        T sum = 0;
        for (size_t i = 0; i < vec.Size(); i++)
        {
            sum += vec[i];
        }

        return sum;
    }

    bool isEmpty()
    {
        if (m_size == 0)
            return true;
        else
            return false;
    }

     size_t resize(int  s) 
    {
        int a = s;
        int x = m_size;
        for (size_t i = a; i < x; i++)
        {
            m_Data[m_size--];
        }

        if (m_size < 0)
        {
            cout << " Vector is empty it can't resize " << endl;
        }
        return m_size;
    }
    
      const T front() const
     {
          if (m_size == 0)
              cout << "Vector is empty " << endl;
         return m_Data[0];
     }

     const T back() const
     {
      
         if (m_size == 0)
             cout << "Vector is empty " << endl;
         return m_Data[m_size - 1];
     }


     const T at(int index) const
     {  
         if (index < 0 || index > m_size)
         {
             cout << " Out of Bound " << endl;
         }

         return m_Data[index];
     }
};
