#ifndef COMPRESS_H
#define COMPRESS_H

/*
 * Receives an unsigned char (byte), an interger to set in the byte and an interger with the displacement as parameter
 * Set the k bits in the byte with the i displacement
 * Returns an unsigned char (byte) with the k bits displaced set
 */
unsigned char set_bit(unsigned char c, int k,int i);
/*
 * Receive destination file, the size of the tree and the garbage of the last byte
 * set the first two bytes of the new file with their respective garbage size and tree size
 */
void set_header(FILE *new_file, short int tree_size, unsigned char trash);
/*
 * Receives the destination file, an string with its tree in preorder and its size
 * Put on file this string
 */
void set_tree(FILE *new_file, unsigned char *string_tree, short int size);
/*
 * Receives a pointer to the source file, a pointer to the destination file (compressed), hash table(dictionary) and a pointer to a Huffman Tree as parameter
 * Writes the compressed file
 */
void write_the_compressed_file(FILE *file_src, FILE *file_dtn, hash_table *hash, int file_size, huffman_tree *tree);

/*
 * Receives a pointer to the source file, a pointer to the destination file (compressed)
 * Compress main function, calls needed functions
 */
void compress(FILE* file_src,int file_size,FILE* file_dtn);

#endif