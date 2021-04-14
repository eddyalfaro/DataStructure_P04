/*
 * main.cpp
 *
 *  Created on: Apr 9, 2021
 *      Author: eddy_
 */


#include <iostream>


using namespace std;
#include "BinarySearchTree.h"
#include "Exception.h"

const char INSERT = 'I', REMOVE = 'R', FIND = 'F', SEARCH = 'S', PRINT = 'P';

int main()
{
	char command;
	int xVal, yVal, info;
	BinarySearchTree<int>* xTree;

	while (!cin.eof()){
		cin >> command;

		switch (command){
		case INSERT:
			cin >> xVal >> yVal >> info;
			cout << xVal <<  " " << yVal << endl;
			break;
		case REMOVE:
		case FIND:
		case SEARCH:
		case PRINT:

		default:
			break;
		}
	}

    return 0;
}
