/** Miguel Vargas
  *
  * BitInputStream.cpp
  *
  * BitinputStream will read the compressed files as a 
  * text file Compress/Uncompress a small file. More or 
  * less a buffer that holds streams that have been 
  * received from the source in one large chunk until 
  * the user needs them. 
  */

#ifndef BITINPUTSTREAM_CPP
#define BITINPUTSTREAM_CPP

#include "BitInputStream.hpp"

/** This method will make a fill a buffer from ifstream
  * and extract bit by bit (8 bits = 1 byte) & return 
  * the bit value.
  */
int BitInputStream::readBit() {
  int bit = 256;

  // Check if stream is good
  if(!in.good())
    return -1;

  // If buffer is full, fill buffer with next input
  if (nbits == 8)
    fill();

  // Extract bit to buffer LSB
  bit = (bit & buf) >> 8;

  // Clear the LSB
  buf = buf << 1;

  // Increment bit count
  ++nbits;

  return bit;
}

/** This function reads an entire int from the ifstream
  * returns that value.
  */
int BitInputStream::readInt() {

	int i;
	in.read((char*)&i, sizeof(int));

	return i;
}

/* Fill the buffer from the input */
void BitInputStream::fill() {
	buf = in.get();
	nbits = 0;
}

#endif