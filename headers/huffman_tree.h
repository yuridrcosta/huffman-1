#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H
#define MAX_SIZE 256

typedef struct huffman_tree huffman_tree;
typedef struct priority_queue queue;
typedef struct hash_table hash_table;
typedef struct node node;

struct huffman_tree
{
	int priority;
	unsigned char item;
	huffman_tree* left;
	huffman_tree* right;
	huffman_tree* next;
};
struct priority_queue
{
	huffman_tree* head;
};
struct node
{
	void* key;
	void* value;	
};
struct hash_table
{
	node* table[MAX_SIZE];
};
/*
 * Receives a pointer to a Queue as parameter
 * Returns an interger, 1 if it's empty, 0 if it's not empty
 */
int is_empty_queue(queue* pq);

/*
 * Receives a Byte (type unsigned char) and the frequency (type interger) as parameter
 * Alocates a Huffman Tree leaf structure in memory and gets a pointer to it. Set the byte which this structure represents and it's frequency
 * Returns an pointer to the created Huffman Tree leaf
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
 * Receives a pointer to a Huffman Tree and a pointer to the source file as parameter
 * Builds a Huffman Tree from a pre order printed tree (based in Huffman Tree rules)
 * Returns a pointer to a Huffman Tree
 */
void* build_huffman_tree(huffman_tree *ht,FILE *file);
/*
 * Receives one pointer to huffman tree, an hash table,pointer to string and how depth the tree is
 * Put on string '0' if follow the left tree pointer or "1" if follow the right tree pointer in their respective depths
 * If it's a leaf, copy this string with its encoding and put it in the hash table
 */
void mapping(huffman_tree *tree, hash_table *ht, unsigned char *code, int depth);
/*
 * Receives the huffman tree
 * Calls mapping to get your hash table 
 */
hash_table* tree_to_table(huffman_tree *tree);
/*
 * Receives the huffman tree and an pointer to short int "id"
 * Creates an string with tree in pre order
 * This "id" representative the current index of this string and the string size
 */
void traversal_pre_order(huffman_tree *tree, short int *id);
/*
 * Receives the huffman tree and an pointer to short int "id"
 * Allocate space for a string with the maximum possible tree size
 * Calls traversal_pre_order to fill string with pre order tree
 * Returns an pointer to string
 */
unsigned char* traversal_tree(huffman_tree *tree, short int *id);

#endif
