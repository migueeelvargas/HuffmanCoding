/** Miguel Vargas
  *
  * HCTree.hpp
  *
  * This file declares all the functions
  * for HCTree class.
  */
#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <queue>
#include <vector>
#include <fstream>
#include "HCNode.hpp"
#include <stack>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;

/** A 'function class' for use as the Compare class in a
 *  priority_queue<HCNode*>.
 *  For this to work, operator< must be defined to
 *  do the right thing on HCNodes.
 */
class HCNodePtrComp {
public:
    bool operator()(HCNode*& lhs, HCNode*& rhs) const {
        return *lhs < *rhs;
    }
};

/** A Huffman Code Tree class.
 *  Not very generic:  Use only if alphabet consists
 *  of unsigned chars.
 */
class HCTree {
private:
    HCNode* root;
    vector<HCNode*> leaves;    

    /** This function allocates memory for all the symbols
      * as leaves in the HCTree. And will add each leaf to the
      * tree's priority queue.
      *
      * Parameters: a const reference to the frequencies &
      * a reference to the tree's priority queue.
      */
    void addLeaves(const vector<int>& freqs,
        priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp>& pq);

    /** This function handles the construction of the Huffman tree.
      * 
      * Parameters: a reference to the HCTree's priority queue.
      */
    void buildTree(priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp>& pq);

    void deleteAll(HCNode* root);
public:
    

    explicit HCTree() : root(0) {
        leaves = vector<HCNode*>(256, (HCNode*) 0);
    }

    ~HCTree();

    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void build(const vector<int>& freqs);

    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    void encode(byte symbol, BitOutputStream& out) const;

    /** Write to the given ofstream
     *  the sequence of bits (as ASCII) coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
     *  BE USED IN THE FINAL SUBMISSION.
     */
    //void encode(byte symbol, ofstream& out) const;


    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    int decode(BitInputStream& in) const;

    /** Return the symbol coded in the next sequence of bits (represented as 
     *  ASCII text) from the ifstream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
     *  IN THE FINAL SUBMISSION.
     */
    // int decode(ifstream& in) const;

    /* Additional helper functions */

    /** This function is used to find the corresponding paths for 
      * all of the leaf nodes in the HCTree. It will store the path
      * a specific stack found in each leaf node.
      * 
      * Parameters: a reference to the tree's leaves.
      */
    void findLeavesPath(vector<HCNode*> &leaves);

    /** Getter function the HCTree's leaves vector
      */
    vector<HCNode*> getLeaves() const;

};

#endif // HCTREE_HPP
