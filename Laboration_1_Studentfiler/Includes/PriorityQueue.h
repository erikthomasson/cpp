#include <memory>
#include <cstdlib>
#include <exception>
#include <utility>
#include <iterator>


template <typename T>
class PriorityQueue{
    private:
        size_t cap=0;
        struct Node{
            T value;
            Node *nextNode = nullptr;
        };
        Node *first = nullptr, *back= nullptr;
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
PriorityQueue<T>::~PriorityQueue(){
    if(first != nullptr){
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
void PriorityQueue<T>::enqueue(const T &element){
    Node *newNode = new Node;
    newNode->value = element;
    newNode->nextNode = nullptr;
    if(first == nullptr){
        first = newNode;
        back = newNode;
    }
    else{
        Node *temp= first;
        if(newNode->value >= back->value){
            back->nextNode = newNode;
            back = newNode;
        }
        else if (newNode->value < first->value)
        {
            newNode->nextNode = first;
            first=newNode;
        }
        else{
            std::cout<<temp->nextNode->value<<std::endl;
            std::cout<<newNode->value<<std::endl;
            
            while(temp->nextNode->value < newNode->value){
                temp = temp->nextNode;
            }
            
            newNode->nextNode = temp->nextNode;
            temp->nextNode = newNode;

        }

    }
    ++cap;
}

template <typename T>
void PriorityQueue<T>::dequeue(){
    try{
    if(cap < 1){
        throw "ERROR: The Queue is empty";
    }
    Node *temp = first->nextNode;
    delete first;
    first = temp;
    this->cap--;
    }catch (const std::exception &e){
        std::cerr<<e.what()<<"\n";
    }
}

template <typename T>
T PriorityQueue<T>::peek() const{
    if(this->isEmpty()) throw "ERROR: The Queue is empty";
        return first->value;
   
}

template <typename T>
size_t PriorityQueue<T>::size() const{
    return this->cap;
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const{
    return this->cap == 0;
}
