/*
 * Node.h
 *
 *  Created on: Apr 9, 2021
 *      Author: eddy_
 */

#ifndef NODE_H_
#define NODE_H_

namespace std {

template <class DataType>
class Node {


	// Methods
	public:
		Node();
		virtual ~Node();

		DataType& getInfo();

};

} /* namespace std */

#endif /* NODE_H_ */
