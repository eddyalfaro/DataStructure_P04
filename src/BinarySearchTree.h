/*
 *    Data Structures Featuring C++  (c) 2021 Sridhar Radhakrishnan
 */

#include <iostream>
using namespace std;

#ifndef __BINARYSEARCHTREE__H
#define __BINARYSEARCHTREE__H


int max (int a, int b)
{
	if (a < b) return b;
	else return a;
}

class Exception {};

class BinaryTreeException : Exception {};
class BinaryTreeMemory : BinaryTreeException {};
class BinaryTreeEmptyTree : BinaryTreeException {};

class BinarySearchTreeException: BinaryTreeException {};
//class BinarySearchTreeChangedSubtree : BinarySearchTreeException {};
class BinarySearchTreeNotFound : BinarySearchTreeException {};

template <class DataType>
class BinarySearchTree;

template <class DataType>
ostream& operator << (ostream& s,  BinarySearchTree<DataType>& X);

// /////////////////////////////////////////////////////////////
template <class DataType>
class BinarySearchTree
// /////////////////////////////////////////////////////////////
{
	friend ostream& operator<< <DataType> (ostream& s,  BinarySearchTree<DataType>& X);
protected:
	DataType* _root;
	BinarySearchTree<DataType>* _left;
	BinarySearchTree<DataType>* _right;
	bool _subtree;

	BinarySearchTree<DataType>* yTree;
	DataType* id;

	virtual BinarySearchTree<DataType>* makeSubtree();
	virtual void copyTree (BinarySearchTree<DataType>* bst);
	virtual void _makeNull ();

	virtual void inorderPrint(ostream& s, bool yTree);
	virtual void preorderPrint(ostream& s, bool yTree);

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
	virtual int yTreeSize();
    // returns the number of nodes in the tree
	virtual DataType& root ();
    // returns data from the root
	virtual BinarySearchTree<DataType>* left ();
    // returns the left subtree
	virtual BinarySearchTree<DataType>* right ();
    // returns the right subtree
	virtual BinarySearchTree<DataType>* getYTree ();
	virtual bool subtree();

	virtual void makeEmpty ();

	virtual DataType find (const DataType& q);
	virtual DataType find (const DataType& x, const DataType& y);

	virtual BinarySearchTree<DataType>* GlobalRebalance(BinarySearchTree<DataType>** inOrderArray, int l, int r);
	virtual void inOrderArray(BinarySearchTree<DataType>** array, int& size);
	virtual void yTreeRebalace(const DataType& xVal);
	virtual int getInorderTraversal(BinarySearchTree<DataType>* node, BinarySearchTree<DataType>** inOrderArray, int& index);

	virtual void remove (const DataType& data);
	virtual void remove (const DataType& x, const DataType& y);

	virtual void rangeSearch (const DataType& low, const DataType& high);
	virtual void rangeSearch (const DataType& x1, const DataType& x2, const DataType& y1, const DataType& y2);

	virtual void insert (const DataType& data);
	virtual void insert (DataType& xVal, DataType& yVal, DataType& id);

};

//AUTOR = Eddy Alfaro
template <class DataType>
ostream& operator<< (ostream& s,  BinarySearchTree<DataType>& X) {
	cout << "INORDER TRAVERSAL: " << endl;
	X.inorderPrint(s, false);
	cout << "PREORDER TRAVERSAL: " << endl;
	X.preorderPrint(s, false);
	return s;
}

// ==============================================================
//AUTOR = Eddy Alfaro
template <class DataType>
void BinarySearchTree<DataType>::inorderPrint(ostream& s, bool yTree){//prints the 2d tree inorder
	if (!yTree){//prints the first nodes of the xtree
		if (this->isEmpty()){
			return;
		}
		_left->inorderPrint(s, false);
		cout << *(_root) << ": " << endl;//prints the node
		this->yTree->inorderPrint(s, true);//calls for printing the nodes in the ytree
		cout << endl;
		_right->inorderPrint(s, false);
	} else {
		if (this->isEmpty()){
				return;
		}
		_left->inorderPrint(s, true);
		cout << " " << *(this->_root) << "(" << *(this->id) << ") ";//prints the root and its id
		_right->inorderPrint(s, true);
	}
}

//AUTOR = Eddy Alfaro
template <class DataType>
void BinarySearchTree<DataType>::preorderPrint(ostream& s, bool yTree){
	if (!yTree){
		if (this->isEmpty()){
			return;
		}
		cout << *(_root) << ": " << endl;
		this->yTree->preorderPrint(s, true);
		cout << endl;
		_left->preorderPrint(s, false);
		_right->preorderPrint(s, false);
	} else {
		if (this->isEmpty()){
				return;
		}
		cout << " " << *(this->_root) << "(" << *(this->id) << ") ";
		_left->preorderPrint(s, true);
		_right->preorderPrint(s, true);
	}
}


template <class DataType>
BinarySearchTree<DataType>::BinarySearchTree ()
{
	_root = NULL;
	_left = NULL;
	_right = NULL;
	yTree = NULL;
	id = NULL;
	_subtree = false;
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>::BinarySearchTree (const DataType& data)
{
	_subtree = false;
	_root = new DataType(data);
	yTree = NULL;
	_left = makeSubtree ();
	_right = makeSubtree ();
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::makeSubtree()
{
	BinarySearchTree<DataType>* bst = new BinarySearchTree<DataType> ();
	bst->_subtree = true;
	return bst;
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>::~BinarySearchTree ()
{
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
// --------------------------------------------------------------
template <class DataType>
bool BinarySearchTree<DataType>::isEmpty()
{
	return (_root == NULL);
}
// --------------------------------------------------------------
template <class DataType>
int BinarySearchTree<DataType>::height ()
{
	if (isEmpty()) return 0;
    return (1 + max (_left->height(), _right->height()));
   	// max() is in stdlib.h
}
// --------------------------------------------------------------
template <class DataType>
int BinarySearchTree<DataType>::size ()
// returns the number of nodes in the tree
{
	if (isEmpty())
		return 0;
	return (1 + _left->size() + _right->size());
}

template <class DataType>
int BinarySearchTree<DataType>::yTreeSize ()
// returns the number of nodes in the tree
{
	if (isEmpty())
		return 0;
	return (1 + yTree->_left->size() + yTree->_right->size());
}
// --------------------------------------------------------------
template <class DataType>
DataType& BinarySearchTree<DataType>::root ()
{
	if (isEmpty()) throw BinaryTreeEmptyTree();
	return *_root;
}
// returns data from the root
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::left () { return _left; }
// returns the left subtree
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::right (){ return _right; }
// returns the right subtree
// --------------------------------------------------------------
//AUTOR = Eddy Alfaro
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::getYTree (){ return yTree; }

template <class DataType>
bool BinarySearchTree<DataType>::subtree() { return _subtree; }
// --------------------------------------------------------------
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
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::copyTree(BinarySearchTree<DataType>* bst)
{
	_root = bst->_root;
	_left = bst->_left;
	_right = bst->_right;
	yTree = bst->yTree;
	id = bst->id;
}
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::_makeNull ()
{
	_root = NULL;
	_left = NULL;
	_right = NULL;
	yTree = NULL;
	id = NULL;
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::_find (const DataType& data)
{
	BinarySearchTree<DataType>* bst = this;

	//cout << "1. FINDING " << data << "..." << endl;
	while (true)
	{
		if (bst->isEmpty()){
			//cout << "Current node is empty" << endl;
			//cout << "returning node with adress " << &(*bst) << endl;
			return bst;
		}
		if (*(bst->_root) < data)
		{
			//cout << "current node is " << *(bst->_root) << " lower than " << data << " moving to the right" << endl;
			bst = bst->_right;
		}
		else if (*(bst->_root) > data)
		{
			//cout << "current node is " << *(bst->_root) << " greater than " << data << " moving to the left" << endl;
            bst = bst->_left;
		}
		else
		{
			//cout << "current node is " << *(bst->_root) << " equal to " << data << " returning " << &(*bst) << " node" << endl;
			return bst;
		}
	}
}
// --------------------------------------------------------------
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
		cout << "\nSorry!!! Element is not found in the tree";
		cout << endl;
		return -1;
	}
}

//AUTOR = Eddy Alfaro
template <class DataType>
DataType BinarySearchTree<DataType>::find (const DataType& x, const DataType& y){
	BinarySearchTree<DataType>* bst = _find(x);//finds the node that contains xVal

	if (bst->isEmpty()) throw BinarySearchTreeNotFound(); //is the found node is empty, the value is not in the tree

	bst = bst->yTree;//moves to the ytree of the found node
	bst = bst->_find(y);//finds the node that contains the yval in the yTree

	if (bst->isEmpty()) throw BinarySearchTreeNotFound();//if the node is empty the y value does not exist

	cout << "The coordinates " << x << ", " << y << " is found in the tree with ID value " << *bst->id << endl; //print out statement

	return *bst->id;//returns the id of the set of coordinates

}

// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::insert (const DataType& data)
{
	//if (_subtree) throw BinarySearchTreeChangedSubtree();
	BinarySearchTree<DataType>* bst = this;
	if (bst->isEmpty())
	{
		bst->_root = new DataType (data);
		//cout << *_root << " inserted in address: " << &(*bst) << endl;
		bst->_left = makeSubtree ();
		bst->_right = makeSubtree ();
	}
	else
	{
        delete bst->_root;
		bst->_root = new DataType (data);
	}
}
// --------------------------------------------------------------
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

//AUTOR = Eddy Alfaro
template<class DataType>
void BinarySearchTree<DataType>::inOrderArray(BinarySearchTree<DataType>** array, int& size){
	BinarySearchTree<DataType>* bst = this;
	if (bst->isEmpty()){
		return;
	}else {
		bst->_left->inOrderArray(array, size);
		array[size++] = bst;
		bst->_right->inOrderArray(array, size);
	}
}

// --------------------------------------------------------------
template <class DataType>
int BinarySearchTree<DataType>::getInorderTraversal(BinarySearchTree<DataType>* node, BinarySearchTree<DataType>** inOrderArray, int& index)
{
	try{
		if (node->isEmpty()) throw BinarySearchTreeNotFound();
	}
	catch(BinarySearchTreeNotFound e){
		//cout << "No tree for inorder traversal" << endl;
		return index;
	}

	//cout << "value: " << this->root() << endl;
	// cout << "left: " << *(this->left()->_root) << endl;
	// cout << "right: " << *(this->right()->_root) << endl;

	if (!this->isEmpty()) {
		if(node->left()->_root != NULL)
		{
			// cout << "\tcalling left" << endl;
			index = node->left()->getInorderTraversal(node->left(), inOrderArray, index);
		}

		inOrderArray[index++] = node;
		// cout << "index: " << index - 1 << " inOrderArray[i]: " << inOrderArray[index - 1]->root() << endl;

		if(node->right()->_root != NULL)
		{
			// cout << "\tcalling right" << endl;
			index = node->right()->getInorderTraversal(node->right(), inOrderArray, index);
		}
	}
	return index;
}

template<class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::GlobalRebalance(BinarySearchTree<DataType>** inOrderArray, int l, int r)
{

	int mid = 0;
	BinarySearchTree<DataType>* temp = new BinarySearchTree<DataType>();

	if(l <= r)
	{
		mid = ((l + r) / 2);
		temp = inOrderArray[mid];
		temp->_left = GlobalRebalance(inOrderArray, l, mid - 1);
		temp->_right = GlobalRebalance(inOrderArray, mid + 1, r);
	}

	return temp;

}

template <class DataType>
void BinarySearchTree<DataType>::yTreeRebalace(const DataType& xVal){
	BinarySearchTree<DataType>* bstx = _find(xVal);//find the node of the xval to rebalance its tree

	if (bstx->isEmpty()) throw BinarySearchTreeNotFound(); // is here is no node with that value return an exception

	BinarySearchTree<DataType>* bsty = &(*bstx->yTree); //assign the address of the ytee to a pointer
	BinarySearchTree<DataType>* temp = new BinarySearchTree();//create an empty tree

	BinarySearchTree<DataType>** inOrderYTree = new BinarySearchTree *[40];//create an oversize array of pointers to store
																		//the nodes in a sorted list
	int size = 0;//initialize the size of the array

	size = bsty->getInorderTraversal(bsty, inOrderYTree, size);//fill the array with the sorted list of nodes and return its size
	temp = &(*bsty->GlobalRebalance(inOrderYTree, 0, size -1));//create a rebalance tree with the sorted nodes and asign to a temporal pntr
	bstx->yTree = &(*temp);//reasign the pointer of the ytree root to the newlly rebalanced tree

}

template <class DataType>
void BinarySearchTree<DataType>::remove (const DataType& x, const DataType& y){
	BinarySearchTree<DataType>* bstx = _find(x); //finds the x node of the x, y pair
	BinarySearchTree<DataType>* bsty;

	if (bstx->isEmpty()){ //is the node is empty s because the vale is not wihtin the tree
		throw BinarySearchTreeNotFound();// returns an exception
	}

	bsty = bstx->yTree;//if the exception is skipped, the designated y tree to the xvalue is assigned to a temporal pointer
	bsty->remove(y);//the method removed is called to remove the yvalue

	if (bsty->isEmpty()){//once yval is removed, if this was the only node within the tree
		bstx->remove(x); //the node with the xval in the xtree is removed
	}
}
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::rangeSearch (const DataType& low, const DataType& high)
{
	if (isEmpty()) return;
	if (*_root >= low)
    {
        _left->rangeSearch(low,high);
		if (*_root <= high)
		{
			cout << *_root << " ";
		}
    }
	if (*_root <= high)
        _right->rangeSearch(low,high);
}

template <class DataType>
void BinarySearchTree<DataType>::rangeSearch (const DataType& x1, const DataType& x2, const DataType& y1, const DataType& y2)
{
	if (isEmpty()) return;
	if (*_root >= x1) //for nodes that have a value greater than the lower limit
    {
        _left->rangeSearch(x1,x2,y1, y2); //move as far to the left as posible
		if (*_root <= x2) //if the value on the current node is within the range
		{
			cout << *_root << " : "; // print the x value
			this->yTree->rangeSearch(y1, y2); //serach within the ytree for the given range
			cout << endl;
		}
    }
	if (*_root <= x2)//value is still small than the higher limit
        _right->rangeSearch(x1,x2, y1, y2);//move as far to the right as posible
}


template <class DataType>
void BinarySearchTree<DataType>::insert(DataType& xVal, DataType& yVal, DataType& id){
	BinarySearchTree<DataType>* bstx = _find(xVal);//finds the location of the node where x should b inserted

	if (bstx->isEmpty()){//check if the node found is empty
		bstx->insert(xVal);//inserts the value into the empty node

		if (bstx->yTree == NULL){//check if the ytree is null on this empty xtree
			bstx->yTree = new BinarySearchTree(yVal);//creates an instance of the ytree
			bstx->yTree->id = new DataType(id);//creates an instance of the id to the node of the ytree
		}
	}else if (*(bstx->_root) == xVal){//the node found has the same value as the input

		BinarySearchTree<DataType>* bsty = &(*bstx->yTree);//input value will be within the ytree

		bsty = bsty->_find(yVal);//finds a node for the yvalue to be input into the ytree

		if (bsty->isEmpty()){//checks if the node found is empty
			bsty->insert(yVal);//inserts the yvalue into the empty node
			bsty->id = new DataType(id);//assigns the id to the x, y pair

		} else if (*bsty->_root == yVal) //the node already has an id and yvalue
			bsty->id = new DataType(id); //id is repaced
	}
}

#endif
