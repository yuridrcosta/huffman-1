#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Receives an unsigned char (byte), an interger to set in the byte and an interger with the displacement as parameter
 * Set the k bits in the byte with the i displacement
 * Returns an unsigned char (byte) with the k bits displaced set
 */
unsigned char set_bit(unsigned char c, int k,int i);

/*
 * Receives an interger representing the maximum bits number of the representation of a byte from Huffman Tree as parameter
 * Creates a Matrix that will be used as dictionary
 * Returns an void pointer that points to the first member of the matrix
 */
void* created_matrix(int bits_number);

/*
 * Receives an unsigned char (byte) to be put in the matrix, a char array as the matrix (dictionary) and an interger representing the maximum bits number of the representation of a byte from Huffman Tree as parameter
 * Puts an byte representation in the matrix (dictionary)
 */
void put_in_matrix(unsigned char c,char* line,char** m,int bits_number);

/*
 * Receives an pointer to a Huffman Tree, an auxiliary interger, a char array as the matrix (dictionary) and an interger representing the maximum bits number of the representation of a byte from Huffman Tree as parameter
 * Recursive function that generates the byte representation from the tree. pos is an auxiliary interger that receives the position in the compressed byte that will be changed
 */
void generate_byte_from_tree(huffman_tree* ht, char* line, int pos,char** m,int bits_number);

/*
 * Receives a pointer to the source file, a pointer to the destination file (compressed), a char array as the matrix (dictionary) and a pointer to a Huffman Tree as parameter
 * Writes the compressed file
 */
void write_the_compressed_file(FILE* file_src,FILE* file_dtn,char** m,huffman_tree* ht);

/*
 * Receives a pointer to the source file, a pointer to the destination file (compressed)
 * Compress main function, calls needed functions
 */
void compress(FILE* file_src,int file_size,FILE* file_dtn);

#endif




