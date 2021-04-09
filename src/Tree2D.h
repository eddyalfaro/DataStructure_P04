/*
 * Tree2D.h
 *
 *  Created on: Apr 9, 2021
 *      Author: eddy_
 */

#ifndef TREE2D_H_
#define TREE2D_H_

#include "BinarySearchTree.h"

namespace std {

template <class DataType>
class Tree2D : BinarySearchTree<DataType> {

	friend ostream& operator<< <DataType> (ostream& s,  Tree2D<DataType>& X);

	public:
		Tree2D();
		virtual ~Tree2D();

};

} /* namespace std */

#endif /* TREE2D_H_ */
