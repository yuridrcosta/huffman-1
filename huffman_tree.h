#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct huffman_tree huffman_tree;
typedef struct priority_queue queue;

/*
 * Receives a pointer to a Huffman Tree as parameter
 * Returns an integer, 1 if it's empty, 0 if it's not empty
 */
int is_empty_tree(huffman_tree* ht);

/*
 * Receives a pointer to a Queue as parameter
 * Returns an interger, 1 if it's empty, 0 if it's not empty
 */
int is_empty_queue(queue* pq);

/*
 *  Receives a Byte (type unsigned char) and the frequency (type interger) as parameter
 *  Alocates a Huffman Tree leaf structure in memory and gets a pointer to it. Set the byte which this structure represents and it's frequency
 *  Returns an pointer to the created Huffman Tree leaf
 */ 
void* create_node_of_huffman_tree(unsigned char i, int p,huffman_tree* left,huffman_tree* right );

/*
 * Alocates a structure Queue in the memory and gets a pointer to this place in memory
 * Returns the pointer	
 */
void* create_priority_queue();

/*
 * Receives a pointer to a Priority Queue and a pointer to a Node as parameter
 * Enqueue in a queue where the priority is the frequency (how much less frequency it has, sooner it leaves the priority queue)
 * Has no return
 */
void enqueue(queue *pq, huffman_tree* new_node);

/*
 * Receives a pointer to a Priority Queue as parameter
 * Retires the node of the queue
 * Returns a pointer to the dequeued node
 */ 
void* dequeue(queue *pq);

/*
 * Receives a pointer to a char with the name of the file to be compacted as parameter
 * Reads the file to be compressed
 * Return a table with the frequency in each character position
 */
void* read_bits(FILE* file_src,int size);

/*
 * Receives an array with the frequency of each character in the ASCII table as parameter
 * Creates a prority queue with each byte of the file received
 * Returns that priority queue
 */
void* create_huffman_queue(int* table);

/*
 * Receives a Priority Queue as parameter
 * Creates the Huffman Tree of this priority queue
 * Returns a pointer to the root of the Huffman Tree
 */
void* create_huffman_tree(queue* pq);

/*
 * Receives a pointer to a Huffman Tree as parameter
 * Verifies if the current node is a leaf
 * Returns an interger, 1 if it's a leaf, 0 if it's not
 */
int isleaf(huffman_tree* ht);

/*
 * Receives a pointer to a Huffman Tree as parameter
 * Gets the size of a Huffman Tree
 * Returns an interger (short) with the size of the tree
 */
short int tree_size(huffman_tree* ht);

short int maximum_bits_number(huffman_tree* ht);

/*
 * Receives a pointer to a Huffman Tree and a pointer to the destination file as parameter
 * Prints the tree on the file
 */
void put_tree_on_file(huffman_tree* ht,FILE* file_dtn);

/*
 * Receives a pointer to a Huffman Tree and a pointer to the source file as parameter
 * Builds a Huffman Tree from a pre order printed tree (based in Huffman Tree rules)
 * Return a pointer to a Huffman Tree
 */
huffman_tree* build_huffman_tree(huffman_tree *ht,FILE *file);






