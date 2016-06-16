/** Miguel Vargas
  *
  * HCTree.cpp
  *
  * This file implements all the functions
  * from the HCTree header file.
  */
#ifndef HCTREE_CPP
#define HCTREE_CPP

#include "HCTree.hpp"

/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs) {
  priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;

  // Adds leaves
  addLeaves(freqs, pq);

  // Builds tree with given priority queue
  buildTree(pq);
}

/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
 *  BE USED IN THE FINAL SUBMISSION.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
  auto leaves = getLeaves();
  std::stack<int> path = leaves[(int)symbol]->path;

  while(!path.empty()) {
    out.writeBit(path.top());
    path.pop();
  }

}

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */
int HCTree::decode(BitInputStream& in) const {
  int bit;
  HCNode* curr = root;

  while(curr->c0 != NULL && curr->c1 != NULL) {
    bit = in.readBit();
    if(bit == 0)
      curr = curr->c0;
    else
      curr = curr->c1;
  }
  return curr->symbol;
}

/** This function allocates memory for all the symbols
  * as leaves in the HCTree. And will add each leaf to the
  * tree's priority queue.
  *
  * Parameters: a const reference to the frequencies &
  * a reference to the tree's priority queue.
  */
void HCTree::addLeaves(const vector<int>& freqs, 
  priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp>& pq) {
  for(auto i = 0; i < freqs.size(); ++i) {
    if(freqs[i] != 0) {
      leaves[i] = new HCNode(freqs[i], (char)i);
      pq.push(leaves[i]);   
    }
  }
}

/** This function handles the construction of the Huffman tree.
  * 
  * Parameters: a reference to the HCTree's priority queue.
  */
void HCTree::buildTree(priority_queue<HCNode*, vector<HCNode*>, 
                        HCNodePtrComp>& pq) {
  HCNode *curr, *parent, *min1, *min2;

  // Edge case: There's only 1 symbol
  if(pq.size() == 1) {
    curr = pq.top();
    pq.pop();

    // Will make a parent node with the only leaf as a child
    parent = new HCNode(curr->count, 0, curr, NULL, NULL);
    curr->p = parent;
  }

  // When there's more than 1 symbol in the file
  while (pq.size() > 1) {
    // Get the value & pop the top 2 values in the queue
    min1 = pq.top();
    pq.pop();
    min2 = pq.top();
    pq.pop();

    // Make new node with combined counts & pointers to the leaves
    parent = new HCNode(min1->count + min2->count, 
                        min1->symbol + min2->symbol, min1, min2, NULL);

    // Update the leaves' parent pointers
    min1->p = parent;
    min2->p = parent;

    // Push the new parent node to the priority queue
    pq.push(parent);
  }
  // Update the root
  root = pq.top();
}

/** This function is used to find the corresponding paths for 
  * all of the leaf nodes in the HCTree. It will store the path
  * in a specific stack found in each leaf node. It will traverse
  * the tree for each leaf node & push a '0' or '1' to leaf's path.
  * 
  * Parameters: a reference to the tree's leaves.
  */
void HCTree::findLeavesPath(vector<HCNode*> &leaves) {
  HCNode* curr;

  for (auto i = 0; i != leaves.size(); ++i) {
    if (leaves[i] != NULL) {
      curr = leaves[i];

      while (curr->p != NULL) {
        if (curr->p->c0 == curr)
          leaves[i]->path.push(0);

        else 
          leaves[i]->path.push(1);
        curr = curr->p;
      }
    }
  }
}

/** Getter function the HCTree's leaves vector
  */
vector<HCNode*> HCTree::getLeaves() const { return leaves; }

HCTree::~HCTree() {
  deleteAll(root);
}

/** A recursive function that frees all the memory
  * allocation of all the nodes used in the HCTree
  *
  * Parameters: a pointer to top most node (root);
  */
void HCTree::deleteAll(HCNode* n) {
  if (n == NULL)
    return;

  deleteAll(n->c0);
  deleteAll(n->c1);

  delete n;
}

#endif










