/*
 * main.cpp
 *
 *  Created on: Apr 9, 2021
 *      Author: eddy_
 */


#include <iostream>


using namespace std;
#include "BinarySearchTree.h"

const char INSERT = 'I', REMOVE = 'R', FIND = 'F', SEARCH = 'S', PRINT = 'P', BALANCE = 'Y';

int main()
{
	char command;
	int xVal, yVal, info;
	int x1, x2, y1, y2;
	BinarySearchTree<int> xTree;

	while (cin >> command){
		switch (command){
		case INSERT:
			cin >> xVal >> yVal >> info;
			cout << xVal <<  " " << yVal << " " << info << endl;
			xTree.insert(xVal, yVal, info);
			break;
		case REMOVE:
			cin >> xVal >> yVal;
			cout << "Remove: " << xVal << ' ' << yVal << endl;
			try {
				xTree.remove(xVal, yVal);
			}catch(BinarySearchTreeNotFound e){
				cout << "The element you are trying to remove is not in the tree " << endl;
				break;
			}
			break;
		case FIND:
			cin >> xVal >> yVal;
			cout << "Find: " << xVal << ' ' << yVal << endl << endl;
			try {
				xTree.find(xVal, yVal);
			}catch (BinarySearchTreeNotFound e){
				cout << "Sorry!!! Coordinate is not found in the X tree" << endl;
				break;
			}
			break;
		case BALANCE:
			cout << "Y tree balance" << endl;
			cin >> xVal;
			cout << xVal << endl;
			xTree.yTreeRebalace(xVal);
			break;
		case SEARCH:
			cout << "Range search " << endl;
			cin >> x1 >> x2 >> y1 >> y2;
			cout << x1 << ' ' << x2 << ' ' << y1 << ' ' << y2 << endl;
			xTree.rangeSearch(x1, x2, y1, y2);
			break;
		case PRINT:
			cout << "Print" << endl;
			cout << xTree << endl;
			break;
		default:
			break;
		}
	}

    return 0;
}
