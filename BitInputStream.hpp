/** Miguel Vargas
  *
  * BitInputStream.hpp
  *
  * Header file for: BitInputStream
  */

#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

class BitInputStream {
private:
	char buf;
	int nbits;
	std::istream& in;
	
public:
	/* Constructor */
	BitInputStream(std::istream& is ) : in(is) {
		buf = 0;		// clear buffer
		nbits = 8;	// initialize bit index
	}

  /** This method will make a fill a buffer from ifstream
    * and extract bit by bit (8 bits = 1 byte) & return 
    * the bit value.
    */
	int readBit();

	/** This function reads an entire int from the ifstream
	  * returns that value.
	  */
	int readInt();

	/* Fill the buffer from the input */
	void fill();
};

#endif