#Huffman Coding

Huffman coding is a loseless data compression algorithm. The idea is that a file is taken and each character that is found in it is given a prefix code. The prefix varies in length. The most frequent character would receive the shorter length, while the prefixes of the longer characters are longer.

The binary representation each character is 1 byte. Thus, each character has an 8-bit representation. With Huffman's Algorithm, we are able to take to take those characters that appear more often in a file & shorten that bit-level representation into shorter codes. Thus, we are then able to take these shorter code & rewrite the actual file with the new codes & the new file will reflect a new compacted size.

##Optimality
Huffman's algorithm is ideal when the entropy of the character distribution is high. This means that if the character distribution is uniform the code length of characters will not be optimal. Thus, a file with a higher character randomness is needed to obtain the most optimal code. 

##Implementation
This repository contains 2 programs: *compress* & *uncompress*. As the titles state, the *compress* program will handle the task of reading a text file & will produce an encoded output file with the optimal compression based of Huffman's algorithm. The *uncompress* program will, then, handle the task of reading the encoded file & will produce an identical copy of the original file.

###Compress program
The program runs as follows: `./compress infile outfile`
The flow of the program:
1. Open & read the original file.
2. Read the file byte-to-byte & keep count of the occurrence of each byte value. Close the file.
3. Using the byte value counts, create a leaf node for each non-zero count. 
4. Now, these nodes are then used to construct an optimal tree using Huffman's algorithm.
5. Using a bottom to top traversal of the tree, we are able to find the correspoding prefix code of each character & that's applied to each leaf node.
6. Next, we open the output file & write a header that contains the occurrence count of each character in the ASCII table to it. Given that there is 256 values in ASCII, this header will be the size of 1MB if each count is represented using an int. *This is a naive approach*
7. Following, the input file is opened once again & read through it byte-to-byte, each time taking that byte value & writing it's prefix code to the provided output file.
8. The output file will now have the full encoding & both input & output file streams are closed.

###Uncompress program
The program runs as follows: `./uncompress infile outfile`
