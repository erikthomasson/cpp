#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "DataContainer.hpp"

template <typename T>
class Vector : public DataContainer<T>
{
  private:
    T **arrpointer;
    unsigned int max_size;

  public:
    Vector();
    ~Vector();
    void PushBack(const T &data) override;
    void PushFront(const T &data) override;
    T &operator[](unsigned int index) override;
};

template <typename T>
Vector<T>::Vector() : DataContainer<T>()
{
    max_size = 100;
    arrpointer = new T *[100];
}
template <typename T>
Vector<T>::~Vector()
{
    for (unsigned int i = 0; i < this->size; i++)
        delete arrpointer[i];
    delete[] arrpointer;
}
template <typename T>
T &Vector<T>::operator[](unsigned int index)
{

    if (arrpointer[0] == nullptr)
        throw "ERROR!\nTrying to access element in an empty Vector";
    return *arrpointer[index];

}

template <typename T>
void Vector<T>::PushBack(const T &data)
{
    if (this->size == this->max_size)
    {
        //Creates a new array with twice the size
        T **temp = new T *[this->max_size * 2];
        for (unsigned int i = 0; i < this->size; i++)
        {
            //temp[i] = new T;
            temp[i] = arrpointer[i];
            *temp[i] = *this->arrpointer[i];
            //delete arrpointer[i];
        }
        delete[] this->arrpointer;
        this->arrpointer = temp;
        this->max_size *= 2;
    }
    arrpointer[this->size] = new T(data);
    this->size++;
}
template <typename T>
void Vector<T>::PushFront(const T &data)
{
    if (this->size == this->max_size)
    {
        T **temp = new T *[this->max_size * 2];
        for (int i = (this->size - 1); i >= 0; i--)
        {
            temp[i +1] = arrpointer[i];
            *temp[i + 1] = *arrpointer[i];
        }
        delete[] this->arrpointer;
        this->arrpointer = temp;
        this->max_size *= 2;
    }
    else
    {
        for (int i = (this->size - 1); i >= 0; i--)
        {
            arrpointer[i + 1] = arrpointer[i];
        }
    }
    arrpointer[0] = new T(data);
    this->size++;
}

#endif