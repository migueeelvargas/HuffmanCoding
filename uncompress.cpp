/** Miguel Vargas
  *
  * uncompress.cpp
  *
  * This program takes an encoded/compressed
  * file & converts it back to it's original
  * condition.
  */
#include <iostream>
#include <cstring>
#include <vector>

#include "HCTree.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

/* Helper functions */
bool isInputValid(int argc, char *argv[]);
void getFrequencies (BitInputStream* in);
void decode(BitInputStream* in, ofstream& out);

/* Global variables */
std::vector<int> freqs(256,0);
HCTree* huffman;
int numBytes = 0;

/* Main program */
int main(int argc, char *argv[]) {

  // Check for correct usage
  if (!isInputValid(argc, argv))
    return -1;

  // Open compressed file for reading
  ifstream ifs;
  ifs.open(argv[1], ios::binary);
  BitInputStream* istream = new BitInputStream(ifs);

  // Read the file header & get frequencies
  getFrequencies(istream);

  // Build a tree from the frequencies
  huffman = new HCTree();
  huffman->build(freqs);

  // Open output file
  ofstream ofs;
  ofs.open(argv[2], ios::binary);

  // Write symbols to out file
  decode(istream, ofs);

  // Close & delete all allocated objects
  ifs.close();
  ofs.close();
  delete(huffman);
  delete(istream);

  return 0;
}

/** This function is used to get the frequencies
  * encoded in the in file. Will also find the
  * total bytes in the original file. 
  * 
  * @params: A reference to the encoded file
  */
void getFrequencies (BitInputStream* in) {
  for(auto i = 0; i < freqs.size(); ++i) {
    freqs[i] = in->readInt();
    numBytes += freqs[i];
  }
}

/** This function handles the decoding of the
  * input file. It will convert the encoded file
  * to it's original condition.
  *
  * @params: reference to input & output streams
  */
void decode(BitInputStream* in, ofstream& out) {
  int symbol = 0;

  for (auto i = 0; i < numBytes; ++i) {
    symbol = huffman->decode(*in);
    out.put((char)symbol);
    out.flush();
  }
}

/** This function is used to check for proper class usage
  * Returns true, if correct usage, false otherwise.
  * 
  * @params: argument count & pointer to argument array
  * returns: boolean value
  */
bool isInputValid(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Correct usage : " << std::endl;
    std::cerr << "./uncompress [input] [output]" << std::endl;
    return false;
  }

  if (argv[1] == argv[2]) {
    std::cerr << "Input & output destination must be different" << std::endl;
    return false;
  }
  return true;
}