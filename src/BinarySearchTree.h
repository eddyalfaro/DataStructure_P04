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
	virtual int getInorderTraversal(BinarySearchTree<DataType>* node, BinarySearchTree<DataType>** inOrderArray, int index);

	virtual void remove (const DataType& data);
	virtual void remove (const DataType& x, const DataType& y);

	virtual void rangeSearch (const DataType& low, const DataType& high);
	virtual void rangeSearch (const DataType& x1, const DataType& x2, const DataType& y1, const DataType& y2);

	virtual void insert (const DataType& data);
	virtual void insert (DataType& xVal, DataType& yVal, DataType& id);

};
template <class DataType>
ostream& operator<< (ostream& s,  BinarySearchTree<DataType>& X) {
	cout << "INORDER TRAVERSAL: " << endl;
	X.inorderPrint(s, false);
	cout << "PREORDER TRAVERSAL: " << endl;
	X.preorderPrint(s, false);
	return s;
}

// ==============================================================
template <class DataType>
void BinarySearchTree<DataType>::inorderPrint(ostream& s, bool yTree){
	if (!yTree){
		if (this->isEmpty()){
			return;
		}
		_left->inorderPrint(s, false);
		cout << *(_root) << ": " << endl;
		this->yTree->inorderPrint(s, true);
		cout << endl;
		_right->inorderPrint(s, false);
	} else {
		if (this->isEmpty()){
				return;
		}
		_left->inorderPrint(s, true);
		cout << " " << *(this->_root) << "(" << *(this->id) << ") ";
		_right->inorderPrint(s, true);
	}
}

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
	//if (data == NULL) throw BinaryTreeMemory();
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

template <class DataType>
DataType BinarySearchTree<DataType>::find (const DataType& x, const DataType& y){
	BinarySearchTree<DataType>* bst = _find(x);

	if (bst->isEmpty()) throw BinarySearchTreeNotFound();

	bst = bst->yTree;
	bst = bst->_find(y);

	if (bst->isEmpty()) throw BinarySearchTreeNotFound();

	cout << "The coordinates " << x << ", " << y << " is found in the tree with ID value " << *bst->id << endl;

	return *bst->id;

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
int BinarySearchTree<DataType>::getInorderTraversal(BinarySearchTree<DataType>* node, BinarySearchTree<DataType>** inOrderArray, int index)
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
		//temp->left = this->GlobalRebalance(inOrderArray, l, mid - 1);
		//temp->right = this->GlobalRebalance(inOrderArray, mid + 1, r);
	}

	return temp;
}

template <class DataType>
void BinarySearchTree<DataType>::yTreeRebalace(const DataType& xVal){
	//cout << "REBALANCING YTREE OF " << xVal << endl;
	BinarySearchTree<DataType>* bstx = _find(xVal);

	if (bstx->isEmpty()) throw BinarySearchTreeNotFound();

	//cout << "BEFORE: ";
	BinarySearchTree<DataType>* bsty = &(*bstx->yTree);
	//bsty->inorderPrint(std::cout, true);

	BinarySearchTree<DataType>** inOrderYTree = new BinarySearchTree *[40];
	int size = 0;

	size = bsty->getInorderTraversal(bsty, inOrderYTree, size);
	//bsty->GlobalRebalance(inOrderYTree, 0, size - 1);
	//cout << "\nAFTER: ";
	//bsty->inorderPrint(std::cout, true);
	//cout << endl;
}

template <class DataType>
void BinarySearchTree<DataType>::remove (const DataType& x, const DataType& y){
	BinarySearchTree<DataType>* bstx = _find(x);
	BinarySearchTree<DataType>* bsty = _find(x);

	if (bstx->isEmpty()){
		throw BinarySearchTreeNotFound();
	}

	bsty = bstx->yTree;
	bsty->remove(y);

	if (bsty->isEmpty()){
		bstx->remove(x);
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
	if (*_root >= x1)
    {
        _left->rangeSearch(x1,x2,y1, y2);
		if (*_root <= x2)
		{
			cout << *_root << " : ";
			this->yTree->rangeSearch(y1, y2);
			cout << endl;
		}
    }
	if (*_root <= x2)
        _right->rangeSearch(x1,x2, y1, y2);
}


template <class DataType>
void BinarySearchTree<DataType>::insert(DataType& xVal, DataType& yVal, DataType& id){
	BinarySearchTree<DataType>* bstx = _find(xVal);//finds the location of the node where x should b inserted
	//cout << endl;
	//cout << "2. INSERTING (" << xVal << ", " << yVal << ") = " << id << endl;
	if (bstx->isEmpty()){
		//cout << "2.1. XTREE INSERTION" << endl;
		//cout << "Node empty...\n";
		//cout << "Adding " << xVal << " to xTree" << endl;
		bstx->insert(xVal);

		//cout << endl;

		if (bstx->yTree == NULL){
			//cout << "2.2. YTREE INSERTION" << endl;
			//cout << "Adding " << yVal << " to yTree" << endl;
			bstx->yTree = new BinarySearchTree(yVal);
			bstx->yTree->id = new DataType(id);
			//cout << *(bstx->yTree->_root) << " inserted in y tree with address: " << &(*bstx->yTree) << endl;

			//cout << "\n2.3. ID added: " << *(bstx->yTree->id) << endl;
			//cout << "\n";
		}
	}else if (*(bstx->_root) == xVal){

		//cout << "\t" << &(*bstx) << " Node populated with " << *(bstx->_root) <<endl;

		//cout << "\n2.";
		BinarySearchTree<DataType>* bsty = &(*bstx->yTree);

		bsty = bsty->_find(yVal);

		if (bsty->isEmpty()){
		//	cout << "Node found empty..." << endl;
		//	cout << "Adding " << yVal << " to yTree" << endl;
			bsty->insert(yVal);
			bsty->id = new DataType(id);

		//	cout << "\n2.2. ID added: " << *(bsty->id) << endl;
		} else if (*bsty->_root == yVal) bsty->id = new DataType(id);
		//cout << endl;
	}
}

#endif
