/*
 * BinarySearchTree.cpp
 *
 *  Created on: Apr 9, 2021
 *      Author: eddy_
 */

#include "BinarySearchTree.h"


namespace std {

template <class DataType>
ostream& operator<< (ostream& s,  BinarySearchTree<DataType>& X) {

	if (!X.isEmpty()) {
		s << *(X.left ()) << " " << X.root () << " " << *(X.right());
	}
	return s;
}

template <class DataType>
BinarySearchTree<DataType>::BinarySearchTree() {
	_root = NULL;
	_left = NULL;
	_right = NULL;
	_subtree = false;
}

template <class DataType>
BinarySearchTree<DataType>::BinarySearchTree (const DataType& data)
{
	_subtree = false;
	_root = new DataType(data);
	_left = makeSubtree ();
	_right = makeSubtree ();
}

template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::makeSubtree()
{
	BinarySearchTree<DataType>* bst = new BinarySearchTree<DataType> ();
	bst->_subtree = true;
	return bst;
}

template <class DataType>
BinarySearchTree<DataType>::~BinarySearchTree() {
	if (_root != NULL)	delete _root;
	_root = NULL;
	if (_left != NULL)	delete _left;
	_left = NULL;
	if (_right != NULL)	delete _right;
	_right = NULL;
}

template <class DataType>
bool BinarySearchTree<DataType>::isEmpty()
{
	return (_root == NULL);
}

template <class DataType>
int BinarySearchTree<DataType>::height ()
{
	if (isEmpty()) return 0;
    return (1 + max (_left->height(), _right->height()));
   	// max() is in stdlib.h
}

template <class DataType>
int BinarySearchTree<DataType>::size ()
// returns the number of nodes in the tree
{
	if (isEmpty())
		return 0;
	return (1 + _left->size() + _right->size());
}

template <class DataType>
DataType& BinarySearchTree<DataType>::root ()
{
	if (isEmpty()) throw BinaryTreeEmptyTree();
	return *_root;
}

template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::left () { return _left; }
// returns the left subtree
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::right (){ return _right; }
// returns the right subtree
// --------------------------------------------------------------
template <class DataType>
bool BinarySearchTree<DataType>::subtree() { return _subtree; }

template <class DataType>
void BinarySearchTree<DataType>::makeEmpty ()
{
	//if (_subtree) throw BinarySearchTreeChangedSubtree();
	if (_root != NULL)
   		delete _root;
    _root = NULL;
	if (_left != NULL)
	   	delete _left;
    _left = NULL;
	if (_right != NULL)
	   	delete _right;
    _right = NULL;
}

template <class DataType>
void BinarySearchTree<DataType>::copyTree(BinarySearchTree<DataType>* bst)
{
	_root = bst->_root;
	_left = bst->_left;
	_right = bst->_right;
}
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::_makeNull ()
{
	_root = NULL;
	_left = NULL;
	_right = NULL;
}

template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::_find (const DataType& data)
{
	BinarySearchTree<DataType>* bst = this;
	while (true)
	{
		if (bst->isEmpty())
			return bst;
		if (*(bst->_root) < data)
		{
			bst = bst->_right;
		}
		else if (*(bst->_root) > data)
		{
            bst = bst->_left;
		}
		else
		{
			return bst;
		}
	}
}

template <class DataType>
DataType BinarySearchTree<DataType>::find (const DataType& q)
{
	BinarySearchTree<DataType>* bst = _find (q);
	try{
		if (bst->isEmpty()) throw BinarySearchTreeNotFound();
		cout<<"\nThe element "<<bst->root()<<" is found in the tree"<<endl;
		return bst->root();
	}
	catch(Exception e)
	{
		cout<<"\nSorry!!! Element is not found in the tree"<<endl;
		return -1;
	}
}

template <class DataType>
void BinarySearchTree<DataType>::insert (const DataType& data)
{
	//if (_subtree) throw BinarySearchTreeChangedSubtree();
	BinarySearchTree<DataType>* bst = _find (data);
	if (bst->isEmpty())
	{
		bst->_root = new DataType (data);
		bst->_left = makeSubtree ();
		bst->_right = makeSubtree ();
	}
	else
	{
        delete bst->_root;
		bst->_root = new DataType (data);
	}
}

template <class DataType>
void BinarySearchTree<DataType>::remove (const DataType& data)
{
	//if (_subtree) throw BinarySearchTreeChangedSubtree();
	BinarySearchTree<DataType>* bst;
	BinarySearchTree<DataType>* bst2;
	BinarySearchTree<DataType>* bst3;

	bst = _find (data);
	if (bst->isEmpty()) throw BinarySearchTreeNotFound();

    // dispose of the existing data; the pointer will be overwritten
    delete bst->_root;

    // .............................................................
	if (bst->_left->isEmpty())
	{
        // the left subtree exists, but the pointer will be overwritten,
        // so we must dispose of it
        delete bst->_left;
        bst2 = bst->_right;		// save the pointer to the right subtree
		bst->copyTree (bst2);	// copy the right subtree;
        // this empties tree if right empty
        bst2->_makeNull ();		// prepare right subtree for deletion
        delete bst2;				// delete right subtree to avoid garbage
	}

	else if (bst->_right->isEmpty())
	{
        // the right subtree exists, but the pointer will be overwritten,
        // so we must dispose of it
        delete bst->_right;
        bst2 = bst->_left;		// save the pointer to the left subtree
		bst->copyTree (bst2);	// copy the left subtree
        bst2->_makeNull ();		// prepare left subtree for deletion
        delete bst2;				// delete left subtree to avoid garbage
	}

	else		// both subtrees non-empty
	{
        // move to the right
		bst2 = bst->_right;
        // then move down to the left as far as possible
		while (!bst2->_left->isEmpty()) bst2 = bst2->_left;
        // overwrite the data pointer
		bst->_root = bst2->_root;

        // bst2's left child is known to be empty and pointer will be overwritten
     	delete bst2->_left;
        // now bst2's right child is copied into it
		if (bst2->_right->isEmpty())
        {
	     	delete bst2->_right;
            bst2->_makeNull();
        }
		else
        {
            bst3 = bst2->_right;
            bst2->copyTree(bst2->_right);
            bst3->_makeNull ();
            delete bst3;
        }
	}
}

template <class DataType>
void BinarySearchTree<DataType>::rangeSearch (const DataType& low, const DataType& high)
{
	if (isEmpty()) return;
	if (*_root >= low)
    {
        _left->rangeSearch(low,high);
		if (*_root <= high)
		{
			cout << *_root << "  ";
		}
    }
	if (*_root <= high)
        _right->rangeSearch(low,high);
}

} /* namespace std */
