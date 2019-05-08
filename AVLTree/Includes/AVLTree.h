//AVLTree implementation with treetraversal, insert, remove, find, getTreeHeight, getMin, getMax.
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
		int height= -1;
		Node *rightChild = nullptr;
		Node *leftChild = nullptr;
	};
	Node *root = nullptr;
	std::vector<T> classVect = {};
	//private help functions
	bool checkDoubleRotation(Node *node, const char &a);
	int getHeight(Node *node);
	size_t fixHeight(Node *a, Node *b);
	void preorder(Node *node);
	void inorder(Node *node);
	void postorder(Node *node);
	Node* deleteMaxNode(Node *node);
	Node* add(T newVal, Node *node);
	Node* rightRotation(Node *node);
	Node* leftRotation(Node *node);
	Node* del(T delVal, Node *node);
public:
	AVLTree() = default;
	void insert(T element);
	void remove(T element);
	bool find(const T &element);
	std::vector<T> preOrderWalk();
	std::vector<T> inOrderWalk();
	std::vector<T> postOrderWalk();
	size_t getTreeHeight();
	T getMin();
	T getMax();
};

template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::del(T delVal, Node *node)
{
	//1: traversing down the tree to remove the selected value 
	//2: Updating the height for the last node 
	//3: balancing the tree of the node and then return upp until the root of the hole tree
	if (node == nullptr)
	{
		throw "Empty Tree";
	}

	if (delVal < node->value)
		node->leftChild = del(delVal, node->leftChild);
	else if (delVal > node->value)
		node->rightChild = del(delVal, node->rightChild);
	else
	{
		// leaf
		if (node->leftChild == nullptr && node->rightChild == nullptr)
		{
			delete node;
			return nullptr;
		}
		// 1 Child
		else if (node->leftChild == nullptr)
		{
			Node *temp = node->rightChild;
			delete node;
			return temp;
		}
		else if (node->rightChild == nullptr)
		{
			Node *temp = node->leftChild;
			delete node;
			return temp;
		}
		else
		{
			//2 Child
			Node *temp = deleteMaxNode(node->leftChild);
			node->value = temp->value;
			node->leftChild = del(temp->value, node->leftChild);
		}

		return node;
	}
	
	node->height = fixHeight(node->leftChild, node->rightChild);

	//Balance the tree

	int left = getHeight(node->leftChild);
	int right = getHeight(node->rightChild);

	if ((left - right) > 1)
	{
		if (checkDoubleRotation(node->leftChild, 'l'))
		{
			node->leftChild = leftRotation(node->leftChild);
		}
		return rightRotation(node);
	}
	if ((right - left) > 1)
	{
		if (checkDoubleRotation(node->rightChild, 'r'))
		{
			node->rightChild = rightRotation(node->rightChild);
		}
		return leftRotation(node);
	}
	return node;
}

template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::leftRotation(Node *node)
{
	//leftrotate the subtree and fixing the height of the nodes
	Node *tempR = node->rightChild;
	Node *tempRL = tempR->leftChild;

	//rotation
	tempR->leftChild = node;
	node->rightChild = tempRL;

	//fix height
	node->height = fixHeight(node->leftChild, node->rightChild);
	tempR->height = fixHeight(tempR->leftChild, tempR->rightChild);
	return tempR;
}


template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::rightRotation(Node *node)
{
	//rightrotate the subtree and fixing the height of the nodes
	Node *tempL = node->leftChild;
	Node *tempLR = tempL->rightChild;

	//rotation
	tempL->rightChild = node;
	node->leftChild = tempLR;

	// height adjustment
	node->height = fixHeight(node->leftChild, node->rightChild);
	tempL->height = fixHeight(tempL->leftChild, tempL->rightChild);

	return tempL;
}


template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::add(T newVal, Node *node)
{
	//1: traversing down the tree to add a new Node and the selected value
	//2: Updating the height  
	//3: balancing the tree of the node and 
	//4: return and do 2,3 for everynode up until the root of the hole tree
	if (node == nullptr)
	{
		Node *newNode = new Node;
		newNode->value = newVal;
		newNode->leftChild = nullptr;
		newNode->rightChild = nullptr;
		newNode->height = 0;
		return newNode;
	}
	if (newVal < node->value)
		node->leftChild = add(newVal, node->leftChild);
	else if (newVal > node->value)
		node->rightChild = add(newVal, node->rightChild);
	else
	{
		// Equal values are not allowed
		throw "Equal values are not allowed";
		return node;
	}

	//fix the height of the node
	node->height = fixHeight(node->leftChild, node->rightChild);

	//balance the tree

	int left = getHeight(node->leftChild);
	int right = getHeight(node->rightChild);

	if ((left - right) > 1)
	{
		if (checkDoubleRotation(node->leftChild, 'l'))
			node->leftChild = leftRotation(node->leftChild);
		return rightRotation(node);
	}
	if ((right - left) > 1)
	{
		if (checkDoubleRotation(node->rightChild, 'r'))
			node->rightChild = rightRotation(node->rightChild);
		return leftRotation(node);
	}
	return node;
}

template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::deleteMaxNode(Node *node)
{
	//remove the Node of the heighest value in the tree inserted
	Node *temp = node;
	while (temp->rightChild != nullptr)
	{
		temp = temp->rightChild;
	}
	return temp;
}

template <typename T>
void AVLTree<T>::preorder(Node *node)
{
	if (node != nullptr)
	{
		this->classVect.push_back(node->value);
		preorder(node->leftChild);
		preorder(node->rightChild);
	}
}
template <typename T>
void AVLTree<T>::inorder(Node *node)
{
	if (node != nullptr)
	{
		inorder(node->leftChild);
		this->classVect.push_back(node->value);
		inorder(node->rightChild);
	}
}
template <typename T>
void AVLTree<T>::postorder(Node *node)
{
	if (node != nullptr)
	{
		postorder(node->leftChild);
		postorder(node->rightChild);
		this->classVect.push_back(node->value);
	}
}

template <typename T>
size_t AVLTree<T>::fixHeight(Node *a, Node *b)
{
	//fixing the height of the node by insert the left and right- Child in the arguments
	if (a == nullptr && b == nullptr)
	{
		return 0;
	}
	else if (a == nullptr)
	{
		return b->height + 1;
	}
	else if (b == nullptr)
	{
		return a->height + 1;
	}
	else
	{
		return (a->height > b->height) ? a->height + 1 : b->height + 1;
	}
}

template <typename T>
int AVLTree<T>::getHeight(Node *node)
{
	//returns the height of the Node
	if (node == nullptr)
	{
		return -1;
	}
	return node->height;
}
template <typename T>
bool AVLTree<T>::checkDoubleRotation(Node *node, const char &a)
{
	//checking if the node needs double rotation
	if (a == 'l' && node->rightChild != nullptr)
	{
		if (getHeight(node->rightChild) > getHeight(node->leftChild))
			return true;
	}
	else if (a == 'r' && node->leftChild != nullptr)
	{
		if (getHeight(node->leftChild) > getHeight(node->rightChild))
			return true;
	}
	return false;
}

template <typename T>
void AVLTree<T>::insert(T element)
{
	root = add(element, this->root);
}

template <typename T>
void AVLTree<T>::remove(T element)
{
	root = del(element, this->root);
}

template <typename T>
bool AVLTree<T>::find(const T &element)
{
	Node *temp = root;
	while (temp != nullptr)
	{
		if (element > temp->value)
		{
			temp = temp->rightChild;
		}
		else if (element < temp->value)
		{
			temp = temp->leftChild;
		}
		else if (temp->value == element)
		{
			return true;
		}
	}
	return false;
}

template <typename T>
std::vector<T> AVLTree<T>::preOrderWalk()
{
	this->classVect = {};
	preorder(this->root);
	return classVect;
}

template <typename T>
std::vector<T> AVLTree<T>::inOrderWalk()
{
	this->classVect = {};
	inorder(this->root);
	return classVect;
}

template <typename T>
std::vector<T> AVLTree<T>::postOrderWalk()
{
	this->classVect = {};
	postorder(this->root);
	return classVect;
}

template <typename T>
size_t AVLTree<T>::getTreeHeight()
{
	if (root == nullptr)
	{
		return -1;
	}
	return root->height;
}

template <typename T>
T AVLTree<T>::getMin()
{
	Node *temp = root;
	if (temp == nullptr)
	{
		throw "Empty Tree";
	}
	else
	{
		while (temp->leftChild != nullptr)
		{
			temp = temp->leftChild;
		}
		return temp->value;
	}
}

template <typename T>
T AVLTree<T>::getMax()
{
	Node *temp = root;
	if (root == nullptr)
	{
		throw "Empty Tree";
	}
	while (temp->rightChild != nullptr)
	{
		temp = temp->rightChild;
	}
	return temp->value;
}
