#include <memory>
#include <cstdlib>
#include <exception>
#include <utility>
#include <iterator>

template <typename T>
class PriorityQueue
{
    //A template Priority Queue class by Erik Thomasson. Priority on the least valuable variable (1<2 or a<b ...)
private:
    size_t cap = 0;
    struct Node
    {
        T value;
        Node *nextNode = nullptr;
    };
    Node *first = nullptr, *back = nullptr;

public:
    PriorityQueue() = default;
    ~PriorityQueue();
    void enqueue(const T &element);
    void dequeue();
    T peek() const;
    size_t size() const;
    bool isEmpty() const;
};

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
    if (first != nullptr)
    {
        Node *deleteNodes = first->nextNode;
        while (deleteNodes->nextNode != nullptr)
        {
            delete first;
            first = deleteNodes;
            deleteNodes = deleteNodes->nextNode;
        }
        delete first;
    }
}

template <typename T>
void PriorityQueue<T>::enqueue(const T &element)
{
    //Adds a new element in the queue
    Node *newNode = new Node;
    newNode->value = element;
    newNode->nextNode = nullptr;
    if (first == nullptr)
    {
        first = newNode;
        back = newNode;
    }
    else
    {
        Node *temp = first;
        if (back->value < newNode->value)
        {
            back->nextNode = newNode;
            back = newNode;
        }
        else if (newNode->value < first->value)
        {
            newNode->nextNode = first;
            first = newNode;
        }
        else
        {
            while (temp->nextNode->value < newNode->value)
            {
                temp = temp->nextNode;
            }

            newNode->nextNode = temp->nextNode;
            temp->nextNode = newNode;
        }
    }
    cap++;
}

template <typename T>
void PriorityQueue<T>::dequeue()
{
    //dequeue the first element in the queue
    if (cap < 1)
    {
        throw "ERROR: The Queue is empty";
    }
    Node *temp = first->nextNode;
    delete first;
    first = temp;
    cap--;
}

template <typename T>
T PriorityQueue<T>::peek() const
{
    //Returns the first element in the queue
    if (this->isEmpty())
        throw "ERROR: The Queue is empty";
    return first->value;
}

template <typename T>
size_t PriorityQueue<T>::size() const
{
    //Function that returns the size of the queue
    return this->cap;
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
    //Function that return if the queue is empty or not
    return this->cap == 0;
}
