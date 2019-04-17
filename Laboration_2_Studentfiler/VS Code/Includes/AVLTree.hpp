#include <memory>
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <utility>
#include <iterator>
#include <vector>
template <typename T>
class AVLTree
{
  private:
	struct Node
	{
		T value;
		size_t height=0;
		Node *rightChild = nullptr;
		Node *leftChild = nullptr;
	};
	Node *root;

  public:
	void insert(T element);
	void remove(T element);
	bool find(T element);
	std::vector<T> preOrderWalk();
	std::vector<T> inOrderWalk();
	std::vector<T> postOrderWalk();
	size_t getTreeHeight();
	T getMin();
	T getMax();
	std::string ToGraphviz()
};

template <typename T>
void AVLTree<T>::insert(T element)
{
	//1: lägg till element
	//2: balansera trädet 
	Node *temp = root;
	void traversing(Node* nextNode,bool &insert = true ,T &newVal = element){
		if( ((this->rightChild->height - this->leftChild->height) > 1) || ((this->leftChild== nullptr) && this->rightChild > 1)){
			//rotation till vänster
			
			Node *tempV = this->rightChild;
			if((tempV->leftChild > tempV->rightChild){
				//dubbel rotation
			}
			else{
				//singel rotation 
				if (tempV->leftChild != nullptr){
					this->rightChild = tempV->leftChild;
					tempV->leftChild = this;
					if (this->leftChild->height < this->rightChild->height) this->height = this->rightChild->height + 1;
				}
				else{
					tempV->leftChild = this; 
					this->rightChild = nullptr;
					this->height = 0;
				}
				
			}
			
		}
		if( ((this->leftChild->height - this->rightChild->height) > 1) || ((this->rightChild == nullptr) && this->leftChild > 1)){
			//rotation till höger
			
			Node *tempR = this->leftChild;
			if((tempR->rightChild > tempR->leftChild){
				//dubbel rotation
			}
			else{
				//singel rotation
				if(tempR->rightChild != nullptr){
				}
				else{

				}
			}
		}
		if(element<this->value && this->leftChild != nullptr){
			return traversing(this->leftChild, false);
		}
		else if (element>this->value && this->rightChild != nullptr){
			return traversing(this->rightChild,false);
		}
		else{
			//de e lika så throwa
		}


		if(element<this->value && this->leftChild == nullptr){
			Node newNode* = new Node;
			newNode->value = element;
			
		}
		else if(element>this->value && this->rightChild == nullptr){
			Node newNode* = new Node;
			newNode->value = element;
		
		}
		else {
			//de e lika så throwa
		}
		return;

	}
}


template <typename T>
void AVLTree<T>::remove(T element) {
	Node *temp = root;
	void traversing(Node* nextNode,bool &insert = true ,T &newVal = element){

	}
}

template <typename T>
bool AVLTree<T>::find(T element)
{
	Node *temp = root;
	while (true)
	{
		if (temp->value > element)
		{
			temp = temp->rightChild;
		}
		else if (temp->value < element)
		{
			temp = temp->leftChild;
		}
		else if (temp->value == element)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

template <typename T>
std::vector<T> AVLTree<T>::preOrderWalk() {}

template <typename T>
std::vector<T> AVLTree<T>::inOrderWalk() {}

template <typename T>
std::vector<T> AVLTree<T>::postOrderWalk() {}

template <typename T>
size_t AVLTree<T>::getTreeHeight()
{
	return this->height;
}

template <typename T>
T AVLTree<T>::getMin()
{
	Node *temp = root;
	while (temp->leftChild != nullptr)
	{
		temp = temp->leftChild;
	}
	return temp->value;
}

template <typename T>
T AVLTree<T>::getMax()
{
	Node *temp = root;
	while (temp->rightChild != nullptr)
	{
		temp = temp->rightChild;
	}
	return temp->value;
}




/*

std::string ToGraphviz() // Member function of the AVLTree class
{
	std::string toReturn = "";
	if(root) // root is a pointer to the root node of the tree
	{
		std::string listOfNodes;
		std::string listOfConnections = std::string("\t\"Root\" -> ") + std::to_string(0) + std::string(";\n");
		toReturn += std::string("digraph {\n");
		size_t id = 0;
		ToGraphvizHelper(listOfNodes, listOfConnections, root, id);
		toReturn += listOfNodes;
		toReturn += listOfConnections;
		toReturn += std::string("}");
	}
	return std::move(toReturn);
}

void ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID) // Member function of the AVLTree class
{
	size_t myID = uniqueID;
	listOfNodes += std::string("\t") + std::to_string(myID) + std::string(" [label=\"") + std::to_string(toWorkWith->element) + std::string("\"];\n");
	if(toWorkWith->leftChild)
	{
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=blue];\n");
		ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->leftChild, ++uniqueID);
	}
	else
	{
		listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
	}
			
	if(toWorkWith->rightChild)
	{
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=red];\n");
		ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->rightChild, ++uniqueID);
	}
	else
	{
		listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
	}
}


*/