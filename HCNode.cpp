/** Miguel Vargas
  *
  * HCnode.cpp
  *
  * This file implements all the functions
  * from the HCNode header file.
  */
#ifndef HCNODE_CPP
#define HCNODE_CPP

#include "HCNode.hpp"

/** This method overrides the '<' operator
  * when comparing nodes. If the counts are the same
  * it will compare the symbols. Else, it will
  * compare the counts of each node.
  *
  * Parameters: a const reference to node
  * Returns: bool result of comparison
  */
bool HCNode::operator<(const HCNode& other) {

	if(count != other.count) return count > other.count;	

	return symbol < other.symbol;
}
#endif