#Huffman Coding

Huffman coding is a loseless data compression algorithm. The idea is that a file is taken and each character that is found in it is given a prefix code. The prefix varies in length. The most frequent character would receive the shorter length, while the prefixes of the longer characters are longer.

The binary representation each character is 1 byte. Thus, each character has an 8-bit representation. With Huffman's Algorithm, we are able to take to take those characters that appear more often in a file & shorten that bit-level representation into shorter codes. Thus, we are then able to take these shorter code & rewrite the actual file with the new codes & the new file will demonstrate new compacted size.

##Optimality
Huffman's algorithm is ideal when the entropy of the character distribution is high. This means that if the character distribution is uniform the code length of characters will not be optimal. Thus, a file with a higher randomness in the distribution of characters is needed for the most optimal code. 
