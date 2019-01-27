#ifndef LZWBINARYTREE_H
#define LZWBINARYTREE_H

#include <iostream>
#include <string>

using namespace std;

template <class itemType>
struct BinaryNode {
        itemType	key;
		string		code;
        BinaryNode *left;
		BinaryNode *right;
        BinaryNode(itemType theKey, string theCode) {
            key		= theKey;
			code	= theCode;
            left	= nullptr;
			right	= nullptr;
        } 
};

template <class itemType>
class BinarySearchTree {
	private:
		BinaryNode<itemType>* root;
		void insert(itemType keyValue, BinaryNode<itemType> *t, string codeValue);
		void makeEmpty(BinaryNode<itemType>* t);
		BinaryNode<itemType>* search(string codeValue, BinaryNode<itemType> *t);
		BinaryNode<itemType>* findMin(BinaryNode<itemType> *t);
        BinaryNode<itemType>* findMax(BinaryNode<itemType> *t);
		itemType keyValue(string codeValue, BinaryNode<itemType> *t);

	public:
		BinarySearchTree<itemType>();
		~BinarySearchTree<itemType>();
		void insert(itemType keyValue, string codeValue);
		void makeEmpty();
		BinaryNode<itemType>* search(string codeValue);
		BinaryNode<itemType>* findMin();
        BinaryNode<itemType>* findMax();
		itemType keyValue(string codeValue);
};

template <class itemType>
BinarySearchTree<itemType>::BinarySearchTree()
{
	root = NULL;
}

template <class itemType>
BinarySearchTree<itemType>::~BinarySearchTree()
{
	makeEmpty();
}

template <class itemType>
void BinarySearchTree<itemType>::insert(itemType keyValue, BinaryNode<itemType> *t, string codeValue)
{
	if(codeValue < t-> code)
	{
		if(t-> left != NULL)
			insert(keyValue, t-> left, codeValue);
		else
			t-> left = new BinaryNode<itemType>(keyValue, codeValue);
	}
	else if(codeValue >= t-> code)
	{
		if(t-> right != NULL)
			insert(keyValue, t-> right, codeValue);
		else
			t-> right = new BinaryNode<itemType>(keyValue, codeValue);
	}
}

template <class itemType>
void BinarySearchTree<itemType>::insert(itemType keyValue, string codeValue)
{
	if(root != NULL)
		insert(keyValue, root, codeValue);
	else
		root = new BinaryNode<itemType>(keyValue, codeValue);
}

template <class itemType>
void BinarySearchTree<itemType>::makeEmpty(BinaryNode<itemType>* t)
{
    if(t != NULL)
    {
        makeEmpty(t-> left);
        makeEmpty(t-> right);
        delete t;
        /*t = NULL;*/
    }
}

template <class itemType>
void BinarySearchTree<itemType>::makeEmpty()
{
	makeEmpty(root);
}

template <class itemType>
BinaryNode<itemType>* BinarySearchTree<itemType>::search(string codeValue, BinaryNode<itemType> *t)
{
	if(t == NULL)
        return NULL;
    else if(codeValue == t-> code)
        return t;
    else if(codeValue < t-> code)
        return search(codeValue, t-> left);
    else if(codeValue > t-> code)
        return search(codeValue, t-> right);
	else
		return NULL;
}

template <class itemType>
BinaryNode<itemType>* BinarySearchTree<itemType>::search(string codeValue)
{
	return search(codeValue, root);
}

template <class itemType>
BinaryNode<itemType> *BinarySearchTree<itemType>::findMin(BinaryNode<itemType> *t)
{
	if(t != NULL) {
		while(t-> left != NULL) {
			t = t-> left;
		}
	}
	return t;
}

template <class itemType>
BinaryNode<itemType> *BinarySearchTree<itemType>::findMin()
{
	return findMin(root);
}

template <class itemType>
BinaryNode<itemType> *BinarySearchTree<itemType>::findMax(BinaryNode<itemType> *t)
{
	if(t != NULL) {
		while(t-> right != NULL) {
			t = t-> right;
		}
	}
	return t;
}

template <class itemType>
BinaryNode<itemType> *BinarySearchTree<itemType>::findMax()
{
	return findMax(root);
}

template <class itemType>
itemType BinarySearchTree<itemType>::keyValue(string codeValue, BinaryNode<itemType> *t)
{
	if(t != NULL) {
		if(codeValue == t-> code)
			return t-> key;
		else if(codeValue < t-> code)
			return keyValue(codeValue, t-> left);
		else
			return keyValue(codeValue, t-> right);
	}
	else
		return -1;
}

template <class itemType>
itemType BinarySearchTree<itemType>::keyValue(string codeValue)
{
	return keyValue(codeValue, root);
}
#endif