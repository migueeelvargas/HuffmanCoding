/** Miguel Vargas
  *
  * compress.cpp
  *
  * This program takes a file in its original
  * encoding & compress it using Huffman's algorithm.
  */
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include "HCTree.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

/* Helper methods */
bool isInputValid(int argc, char *argv[]);
void getFrequencies(ifstream& in, BitInputStream* istream);
void writeHeader(ofstream& out);
void displayTestingInfo(std::vector<HCNode*> leaves);
void encode(ifstream& in, BitInputStream* istream, BitOutputStream* ostream);

/* Global variables */
std::vector<int> freqs(256,0);
int totalBytes = 0;
HCTree* huffman;

/* Main program */
int main(int argc, char *argv[]) {
	// Check for correct input usages
  if (!isInputValid(argc, argv))
    return -1;

  // Get the frequencies from the file
  ifstream ifs;
  ifs.open(argv[1], ios::binary);
  BitInputStream* istream = new BitInputStream(ifs);

  getFrequencies(ifs, istream);
  delete(istream);

  // If blank file was given, return a blank file
  if(totalBytes == 0) {
    ofstream ofs;
    ofs.open(argv[2], ios::binary);
    ofs.close();
    ifs.close();
    delete(huffman);

    return -1;
  }

  // Build the tree
  huffman = new HCTree();
  huffman->build(freqs);

  // Create output file
  ofstream ofs;
  ofs.open(argv[2], ios::binary);
  BitOutputStream* ostream = new BitOutputStream(ofs);

  // Write the header to out file
  auto leaves = huffman->getLeaves();
  huffman->findLeavesPath(leaves);

  // Write header using frequencies
  writeHeader(ofs);

  // Open input file again
  ifs.open(argv[1], ios::binary);
  istream = new BitInputStream(ifs);

  // Encode the file
  encode(ifs, istream, ostream);

  // Close streams
  ifs.close();
  ofs.close();
  delete(istream);
  delete(ostream);
  delete(huffman);

  return 0;
}

/** This class is used to get the frequencies
  * from the original input file. Will also keep
  * count of the total bytes in the file.
  * 
  * @params: A reference to the input file
  */
void getFrequencies (ifstream& in, BitInputStream* istream) {
  unsigned char symbol;
  int nbits = 0;
  int next;

  // Clear the symbol
  symbol = symbol << 8;

  while (1) {
    next = istream->readBit();

    // Extract next (returned) bit into symbol's LSB
    symbol = symbol | next;

    // Clear the LSB
    if(nbits != 7)
      symbol = symbol << 1;

    ++nbits;

    if (!in.good())
      break;

    // With 8 bits, new symbol is read; update frequency.
    if (nbits == 8) {
      freqs[(int)symbol]++;
      ++totalBytes;

      // Clear symbol buffer & reset bit count
      symbol = symbol << 8;
      nbits = 0; 
    }
  }

  in.close();
}

/** This class handles the operation of writing the 
  * header to the compressed. Used to uncompress an
  * encoded file. It will iterate through all of the
  * frequency vector & write the frequency to output.
  *
  * @params: a reference to the output file
  */
void writeHeader(ofstream& out) {
  for(auto i = 0; i < freqs.size(); ++i)
    out.write((char*)&freqs[i], sizeof(int));
}

/** This class handles the process of encoding the 
  * original file to the provided output file. It will
  * read the input & call the encode class provided by
  * the Huffman Tree. 
  *
  * @params: references to the in & out streams
  */
void encode(ifstream& in, BitInputStream* istream, BitOutputStream* ostream) {
  unsigned char symbol;
  int nbits = 0;
  int next;
  auto leaves = huffman->getLeaves();

  symbol = symbol << 8;

  while (1) {
    next = istream->readBit();

    // Extract next (returned) bit into symbol's LSB
    symbol = symbol | next;

    // Clear the LSB
    if (nbits != 7)
      symbol = symbol << 1;

    ++nbits;

    // if end of file is reached, flush the buffer;
    if(in.eof())
      ostream->flush();

    // If end of file reached
    if(!in.good())
      break;

    // With 8 bits, new symbol is read;
    if (nbits == 8) {
      if (symbol == leaves[(int)symbol]->symbol)
        huffman->encode(symbol, *ostream);

      // Clear symbol buffer & reset bit count
      symbol = symbol << 8;
      nbits = 0; 
    }
  }
}

/** This class is used to check for proper class usage
  * Returns true, if correct usage, false otherwise.
  * 
  * @params: argument count & pointer to argument array
  * Returns: a boolean flag
  */
bool isInputValid(int argc, char *argv[]) {
	if (argc != 3) {
		std::cerr << "Correct usage : " << std::endl;
		std::cerr << "./compress [input] [output]" << std::endl;
		return false;
	}

	if (argv[1] == argv[2]) {
		std::cerr << "Input & output destination must be different" << std::endl;
		return false;
	}
  return true;
}

/** This class, while not part of the finished program
  * is used to display the following info: frequencies,
  * file size(total bytes) & the # of unique characters
  *
  * @params: a vector with the tree's leaves.
  */
void displayTestingInfo(std::vector<HCNode*> leaves) {
  
  // Display frequencies - Test
  std::stack<int> thePath;
  for (auto i : leaves) {
    if (i != NULL) {
      thePath = i->path;
      std::cout << i->symbol << " -> ";

      if(thePath.empty())
        std::cout << "empty";

      while(!thePath.empty()) {
        std::cout << thePath.top();
        thePath.pop();
      }
      std::cout << endl;
    }
  }

  // Display the # of bytes - Test
  std::cout << "File size: " << totalBytes << " bytes" << endl;

  // Display the unique characters
  int symbols = 0;
  for(auto i = 0; i < freqs.size(); ++i)
    if (freqs[i] != 0) ++symbols;
  std::cout << "Unique symbols: " << symbols << std::endl;
}