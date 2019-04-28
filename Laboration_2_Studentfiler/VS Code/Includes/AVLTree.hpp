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
	Node* insert(Node *nextNode, T &newVal);
	Node* remove(Node *nextNode, T &delVal);
	Node* rightBalancing(Node *node);
	Node* leftBalancing(Node *node);
	Node* maxValuedelete(Node* node);
	T postOrderWalk(Node*node);
	T inOrderWalk(Node*node);
	T preOrderWalk(Node*node);
	struct Node
	{
		T value;
		size_t height = -1;
		Node *rightChild = nullptr;
		Node *leftChild = nullptr;
	};
	Node *root = nullptr;

  public:
	AVLTree();
	void insert(T element);
	void remove(T element);
	bool find(T element); 
	std::vector<T> preOrderWalk();
	std::vector<T> inOrderWalk();
	std::vector<T> postOrderWalk();
	size_t getTreeHeight(); 
	T getMin();				
	T getMax();				
	

  private: 
	T postOrderWalk(Node* node){
		if(node ==nullptr){
			return;
		}
		postOrderWalk(node->leftChild);
		postOrderWalk(node->rightChild);
		return node->value;

	}
	T inOrderWalk(Node* node){
		if(node ==nullptr){
			return;
		}
		inOrderWalk(node->leftChild);
		return node->value;
		inOrderWalk(node->rightChild);
	}
	T preOrderWalk(Node* node){
		if(node ==nullptr){
			return;
		}
		return node->value;
		preOrderWalk(node->leftChild);
		preOrderWalk(node->rightChild);
	}

	Node* maxValuedelete(Node* node){
		Node* temp = node;
		while(temp->rightChild != nullptr){
			temp = temp->rightChild;
		}
		return temp;
	}

	Node *insert(Node *node, T &newVal)
	{
		//add element
		if (node == nullptr)
		{
			node->value = element;
			newNode->height = 1;
		}

		if (newVal < node->value)
			node->left = insert(node->left, newVal);
		else if (key > node->key)
			node->right = insert(node->right, newVal);
		else
		{
			// Equal values are not allowed
			throw "Equal values are not allowed";
			return node;
		}

		//fix the height
		if (node->leftChild->height > node->rightChild->height)
		{
			node->height = node->leftChild->height + 1;
		}
		else
		{
			node->height = node->rightChild->height + 1;
		}
		
		if ((nextNode->rightChild->height - nextNode->leftChild->height) > 1 && nextNode->height > -1)
			return leftBalancing(nextNode);
		else if (((nextNode->leftChild->height - nextNode->rightChild->height) > 1) && nextNode->height > -1)
			return rightBalancing(nextNode);

		return node;
	}

	Node *rightBalancing(Node *node)
	{
		//rotation till höger
		Node *tempL = node->leftChild;
		if((tempL->rightChild->height > tempL->leftChild->height){
			//dubbel rotation
			Node *tempLeftRight = tempL->rightChild;
			if (tempLeftRight->leftChild != nullptr)
			{
				node->rightChild = tempLeftRight->leftChild;
			}
			else
			{
				node->rightChild = nullptr;
			}
			tempLeftRight->leftChild = node;
			if (tempLeftRight->rightChild != nullptr)
			{
				tempL->leftChild = tempLeftRight->rightChild;
				tempLeftRight->rightChild = tempL;
			}
			else
			{
				tempLeftRight->rightChild = tempL;
				tempL->leftChild = nullptr;
			}

			//height adjustments
			if (node->rightChild->height > node->leftChild->height)
			{
				node->height = node->rightChild->height + 1;
			}
			else
			{
				node->height = node->leftChild->height + 1;
			}
			if (tempL->rightChild->height > tempL->leftChild->height)
			{
				tempL->height = tempL->rightChild->height + 1;
			}
			else
			{
				tempL->height = tempL->leftChild->height + 1;
			}
			if (tempLeftRight->rightChild->height > tempLeftRight->leftChild->height)
			{
				tempLeftRight->height = tempLeftRight->rightChild->height + 1;
			}
			else
			{
				tempLeftRight->height = tempLeftRight->leftChild->height + 1;
			}
			return tempLeftRight;
		
	}

	else{
			//singel rotation
			if (tempL->rightChild != nullptr)
			{
				node->leftChild = tempL->rightChild;
				tempL->rightChild = node;
			}
			else
			{
				tempL->rightChild = node;
				node->leftChild = nullptr;
			}

			// height adjustment
			if (node->rightChild->height > node->leftChild->height)
			{
				node->height = node->rightChild->height + 1;
			}
			else
			{
				node->height = node->leftChild->height + 1;
			}
			if (tempL->rightChild->height > tempL->leftChild->height)
			{
				tempL->height = tempL->rightChild->height + 1;
			}
			else
			{
				tempL->height = tempL->leftChild->height + 1;
			}
			return tempL;
		}
	}

	Node *leftBalancing(Node *node)
	{
		//rotation till vänster
		Node *tempR = node->rightChild;
		if((tempR->leftChild->height > tempR->rightChild->height){
			//dubbel rotation
			Node *tempRightLeft = tempR->leftChild;
			if (tempRightLeft->leftChild != nullptr)
			{
				node->rightChild = tempRightLeft->leftChild;
			}
			else
			{
				node->rightChild = nullptr;
			}
			tempRightLeft->leftChild = node;
			if (tempRightLeft->rightChild != nullptr)
			{
				tempR->leftChild = tempRightLeft->rightChild;
				tempRightLeft->rightChild = tempR;
			}
			else
			{
				tempRightLeft->rightChild = tempR;
				tempR->leftChild = nullptr;
			}

			// height adjustment
			if (node->rightChild->height > node->leftChild->height)
				node->height = node->rightChild->height + 1;
			else
				node->height = node->leftChild->height + 1;
			if (tempR->rightChild->height > tempR->leftChild->height)
				tempR->height = tempR->rightChild->height + 1;
			else
				tempR->height = tempR->leftChild->height + 1;
			if (tempRightLeft->rightChild->height > tempRightLeft->leftChild->height)
				tempRightLeft->height = tempRight->rightChild->height + 1;
			else
				tempRightLeft->height = tempRightLeft->leftChild->height + 1;
			return tempRightLeft;
	}
	else{
			//singel rotation
			if (tempR->leftChild != nullptr)
			{
				node->rightChild = tempR->leftChild;
				tempR->leftChild = node;
			}
			else
			{
				tempR->leftChild = node;
				node->rightChild = nullptr;
			}
	
			// height adjustment
			if (node->rightChild->height > node->leftChild->height)
				node->height = node->rightChild->height + 1;
			else
				node->height = node->leftChild->height + 1;
			if (tempR->rightChild->height > tempR->leftChild->height)
				tempR->height = tempR->rightChild->height + 1;
			else
				tempR->height = tempR->leftChild->height + 1;
			return tempR;
	}
	}


	Node *remove(Node *node, T &delVal)
	{
		
		if (node == nullptr)
		{
			throw "Empty Tree";
			return node;
			//throwa tomt träd
		}

		if (delVal < node->value)
			node->leftChild = remove(node->leftChild, delVal);
		else if (delVal > node->value)
			node->rightChild = remove(node->rightChild, delVal);
		else
		{
			// noll barn
			if(node->leftChild == nullptr && node->rightChild==nullptr){
				delete node;
				return nullptr;	
			}
			// 1 barn
			else if(node->leftChild == nullptr){
				Node *temp = node->rightChild;
				delete node;
				return temp;

			}
			else if(node->rightChild == nullptr){
				Node *temp = node->letChild;
				delete node;
				return temp; 
			}
			else {
				//2 barn
				Node* temp = maxValuedelete(node->leftChild);
				node->value = temp->value;
				node->leftChild = remove(node->leftChild, temp->value);
			}

			return node;
		}

		//fix the height

		if (node->leftChild->height > node->rightChild->height)
		{
			node->height = node->leftChild->height + 1;
		}
		else
		{
			node->height = node->rightChild->height + 1;
		}
		//balance
		if ((nextNode->rightChild->height - nextNode->leftChild->height) > 1 && nextNode->height > -1)
			return leftBalancing(nextNode);
		else if (((nextNode->leftChild->height - nextNode->rightChild->height) > 1) && nextNode->height > -1)
			return rightBalancing(nextNode);

		return node;
	}
};

template <typename T>
AVLTree<T>::AVLTree()
{
	Node *newNode = new Node;
	newNode->rightChild = nullptr;
	newNode->leftChild = nullptr;
	newNode->height = -1; 
	root = newNode;
}

template <typename T>
void AVLTree<T>::insert(T element)
{
	Node *temp = root;
	insert(temp, element);
}

template <typename T>
void AVLTree<T>::remove(T element)
{
	Node *temp = root;
	remove(temp, element);
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
std::vector<T> AVLTree<T>::preOrderWalk() {
	std::vector<T> vect;
	vect.push_back(preOrderWalk(this->root));
	return vect;
}

template <typename T>
std::vector<T> AVLTree<T>::inOrderWalk() {
	std::vector<T> vect;
	vect.push_back(inOrderWalk(this->root));
	return vect;
}

template <typename T>
std::vector<T> AVLTree<T>::postOrderWalk() {
	std::vector<T> vect;
	vect.push_back(postOrderWalk(this->root));
	return vect;
}

template <typename T>
size_t AVLTree<T>::getTreeHeight()
{
	return root->height;
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