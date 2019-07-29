#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "DataContainer.hpp"

template <typename T>
class LinkedList : public DataContainer<T>
{
  private:
    struct Node
    {
        T value;
        Node *nextNode = nullptr;
    };
    Node *firstElement, *lastElement;

  public:
    LinkedList();
    ~LinkedList();
    void PushBack(const T &data) override;
    void PushFront(const T &data) override;
    T &operator[](unsigned int value) override;
};

template <typename T>
LinkedList<T>::LinkedList() : DataContainer<T>()
{

    this->firstElement = nullptr;
    this->lastElement = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    Node *deleteNodes = firstElement->nextNode;
    while (deleteNodes->nextNode != nullptr)
    {
        delete firstElement;
        firstElement = deleteNodes;
        deleteNodes = deleteNodes->nextNode;
    }
    delete firstElement;
}

template <typename T>
void LinkedList<T>::PushBack(const T &data)
{
    Node *newNode = new Node;
    newNode->value = data;
    newNode->nextNode = nullptr;
    if (firstElement == nullptr)
    {
        firstElement = newNode;
        lastElement = newNode;
    }
    else
    {
        lastElement->nextNode = newNode;
        lastElement = lastElement->nextNode;
    }
    this->size++;
}

template <typename T>
void LinkedList<T>::PushFront(const T &data)
{
    Node *newNode = new Node;
    newNode->value = data;
    newNode->nextNode = firstElement;
    if (firstElement == nullptr)
    {
        firstElement = newNode;
        lastElement = newNode;
    }
    else
    {
        firstElement = newNode;
    }
    this->size++;
}

template <typename T>
T &LinkedList<T>::operator[](unsigned int index)
{
    unsigned int i = 0;
    Node *displayValue;

    if (this->firstElement == nullptr)
        throw "ERROR!\nThe Linked List is empty(has no elements)";

    
    displayValue = firstElement;
    while (i < index)
    {
        displayValue = displayValue->nextNode;
        i++;
    }
    return displayValue->value;

}

#endif