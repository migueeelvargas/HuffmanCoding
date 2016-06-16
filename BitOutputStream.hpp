/** Miguel Vargas
  *
  * BitOutputStream.hpp
  *
  *	The header file for all the BitOutputStream's
  * methods.
  */
#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

class BitOutputStream {
private:
	char buf;
	int nbits;
	std::ostream& out;

public:
	BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0) {
		// Clear the buffer & bit counter
	}

	/** This method is used to write a bit to the ofstream.
	  * It will fill a buffer with 8 bits & write each 
	  * bit-by-bit & then flush the buffer & read new 8 bits.
	  */
	void writeBit(int bit);

	/* Send the filled buffer to output & clear it */
	// Method mainly used from in-class slides
	void flush();	
};

#endif