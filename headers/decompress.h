#ifndef DECOMPRESS_H
#define DECOMPRESS_H


/*
 * Receives an unsigned char (byte) and an interger as parameter
 * Verifies if the i bit in the unsigned char (byte) is set
 * Returns an interger, 1 if it's set, 0 if it's not
 */
int is_bit_i_set(unsigned char c, int i);

/*
 * Receives a pointer to the source file (compressed) as parameter
 * Gets the trash size from the compressed file
 * Returns and interger with the size
 */
int trash_length(FILE *file_src);

/*
 *Receives a pointer to the source file (compressed) as parameter
 *Gets the length of the tree in the compressed file
 *Returns an interger with the length
 */
int tree_length(FILE *file_src);

/*
 * Receives a pointer to a Huffman Tree, a pointer to the source file (compressed) and a pointer to the destination file as parameter
 * Writes the decompressed file
 */
void write_the_decompressed_file(huffman_tree* ht,FILE* file_src,FILE* file_dtn);

/*
 * Receives a pointer to the source file (compressed) and a pointer to the destination file as parameter
 * Decompress main fuction, calls the needed functions
 */ 
void decompress(FILE *file_src,FILE *file_dtn);

#endif
