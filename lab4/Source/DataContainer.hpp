#ifndef DATA_CONTAINER_HPP
#define DATA_CONTAINER_HPP
#include <iostream>
#include <string>
#include <exception>
 
template <typename T>
class DataContainer
{
  protected:
    unsigned int size;

  public:
    virtual ~DataContainer() = default;
    DataContainer();
    virtual void PushBack(const T &data) = 0;
    virtual void PushFront(const T &data) = 0;
    virtual T &operator[](unsigned int index) = 0;
    unsigned int Size() const;
};
template <typename T>
DataContainer<T>::DataContainer()
{
    this->size = 0;
}

template <typename T>
unsigned int DataContainer<T>::Size() const
{
    return this->size;
}

#endif