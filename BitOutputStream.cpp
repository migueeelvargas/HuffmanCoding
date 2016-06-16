/** Miguel Vargas
  *
  * BitOutputStream.cpp
  *
  * BitOuputStream will Output buffering through 
  *	the buffer holds items destined for output 
  * until there are enough of them to send to the 
  * destination; then they are sent in one large chunk
  */
#ifndef BITOUTPUTSTREAM_CPP
#define BITOUTPUTSTREAM_CPP

#include "BitOutputStream.hpp"

/** This method is used to write a bit to the ofstream.
  * It will fill a buffer with 8 bits & write each 
  * bit-by-bit & then flush the buffer & read new 8 bits.
  */
void BitOutputStream::writeBit(int bit) {

	// Clears LSB & extract bit to buffer.
	buf = (buf << 1) | bit;

	// Increment the count
	++nbits;

	// When buffer is full, flush it.
	if(nbits == 8) {
		out.put(buf);
		out.flush();
		nbits = 0;
	}
}

/* Send the filled buffer to output & clear it */
void BitOutputStream::flush() {
	buf = buf << (8 - nbits);
	out.put(buf);
	out.flush();
	buf = nbits = 0;
}
#endif