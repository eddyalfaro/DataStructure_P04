/*
 * BinarySearchTree.h
 *
 *  Created on: Apr 9, 2021
 *      Author: eddy_
 */

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include <iostream>
#include "Exception.h"
#include "Node.h"

namespace std {

class BinaryTreeException : Exception {};
class BinaryTreeMemory : BinaryTreeException {};
class BinaryTreeEmptyTree : BinaryTreeException {};

class BinarySearchTreeException: BinaryTreeException {};
class BinarySearchTreeChangedSubtree : BinarySearchTreeException {};
class BinarySearchTreeNotFound : BinarySearchTreeException {};

template <class DataType>
class BinarySearchTree {

	friend ostream& operator<< <DataType> (ostream& s,  BinarySearchTree<DataType>& X);

	protected:

		Node<DataType>* _root;
		BinarySearchTree<DataType>* _left;
		BinarySearchTree<DataType>* _right;
		bool _subtree;

		virtual BinarySearchTree<DataType>* makeSubtree();
		virtual void copyTree (BinarySearchTree<DataType>* bst);
		virtual void _makeNull ();
		BinarySearchTree<DataType>* _find (const DataType& data);

	public:

		BinarySearchTree ();
		BinarySearchTree (const DataType& data);

		virtual ~BinarySearchTree ();

		virtual bool isEmpty();
	    // returns true if tree is empty,
	    // but otherwise returns false

		virtual int height ();
	    // returns the height (or depth) of the tree

		virtual int size ();
	    // returns the number of nodes in the tree

		virtual DataType& root ();
	    // returns data from the root

		virtual BinarySearchTree<DataType>* left ();
	    // returns the left subtree

		virtual BinarySearchTree<DataType>* right ();
	    // returns the right subtree

		virtual bool subtree();
		virtual void makeEmpty ();
		virtual DataType find (const DataType& q);
		virtual void remove (const DataType& data);
		virtual void rangeSearch (const DataType& low, const DataType& high);
		virtual void insert (const DataType& data);
};

} /* namespace std */

#endif /* BINARYSEARCHTREE_H_ */
