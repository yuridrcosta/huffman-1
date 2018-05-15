#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/huffman_tree.h"
#include "../headers/hash_table.h"
#include "../headers/decompress.h"
#include "../headers/compress.h"

int is_empty_queue(queue* pq)
{
	if(pq->head == NULL)  return 1;

	return 0;
}
void* create_node_of_huffman_tree(unsigned char i, int p,huffman_tree* left,huffman_tree* right )
{
	huffman_tree* new_leaf = (huffman_tree*) malloc(sizeof(huffman_tree));
	new_leaf->item = i;
	new_leaf->priority = p;
	new_leaf->left = left;
	new_leaf->right = right;
	return (void*) new_leaf;
}
void* create_priority_queue()
{
	queue* new_queue = (queue*) malloc(sizeof(queue));
	new_queue->head = NULL;
	return (void*) new_queue;
}
void enqueue(queue *pq, huffman_tree* new_node)
{
	int p = new_node->priority;

	if ((is_empty_queue(pq)) || (p <= pq->head->priority)) 
	{
		new_node->next = pq->head;
		pq->head = new_node;
	} 
	else 
	{
		huffman_tree *current = pq->head;
		while((current->next != NULL) && (current->next->priority < p)) 
			{
				current = current->next;
			}
			new_node->next = current->next;
			current->next = new_node;
	}
} 
void* dequeue(queue *pq)
{
	if(is_empty_queue(pq))	return NULL;

	huffman_tree *node = pq->head;
	pq->head = pq->head->next;
	node->next = NULL;
	return (void*) node;
}
void* read_bits(FILE* file_src,int size)
{

	int* table = (int*) malloc(sizeof(int)*256);
	int i;

	memset(table,0,sizeof(int)*256);

	for(i = 0; i < size;++i)
		table[getc(file_src)]++;

	fseek(file_src, 0, SEEK_SET);

	return (void*) table;
}
void* create_huffman_queue(int* table)
{
	int i;
	queue* pq = (queue*) create_priority_queue();

	for(i = 0;i < 256;++i)
		if(table[i])
			enqueue(pq,create_node_of_huffman_tree(i,table[i],NULL,NULL));

  	free(table);

	return (void*) pq;
}
void* create_huffman_tree(queue* pq)
{
	huffman_tree* new_node_to_enqueue;
	huffman_tree* ht;

	unsigned char asterisco = '*';

	if(pq->head == NULL)	return NULL;

	if(pq->head->next == NULL)
	{
		huffman_tree* left_tree = dequeue(pq);
		new_node_to_enqueue = create_node_of_huffman_tree(asterisco,left_tree->priority,left_tree,NULL);

		enqueue(pq,new_node_to_enqueue);
	}
	while(pq->head->next != NULL)	
	{	
		huffman_tree* left_tree = dequeue(pq);
		huffman_tree* right_tree = dequeue(pq);

		new_node_to_enqueue = create_node_of_huffman_tree(asterisco,(left_tree->priority + right_tree->priority),left_tree,right_tree);

		enqueue(pq,new_node_to_enqueue);
	}

	ht = pq->head;

	free(pq);

	return (void*) ht;
}
int isleaf(huffman_tree* ht)
{	
	if(ht->left == NULL && ht->right == NULL)	return 1;

	return 0;	
}
void* build_huffman_tree(huffman_tree *ht,FILE *file)
{
	unsigned char byte;

	byte =  getc(file);

	if(byte == '*')
	{
		ht = create_node_of_huffman_tree(byte,0,NULL,NULL);
		ht->left = build_huffman_tree(ht->left,file);
		ht->right = build_huffman_tree(ht->right,file);
	}
	else
	{
		if(byte == '\\')//scape
		{
			byte = getc(file);//next
			ht = create_node_of_huffman_tree(byte,0,NULL,NULL);
		}

		else	ht= create_node_of_huffman_tree(byte,0,NULL,NULL);
	}
	return (void*)ht;
}
void mapping(huffman_tree *tree, hash_table *ht, unsigned char *code, int depth)
{
	if(tree == NULL) return;
  
	if(isleaf(tree))
	{
		unsigned char *value = (unsigned char*) malloc(15 * sizeof(unsigned char));
		strcpy(value, code);

		unsigned char *item = (unsigned char *) malloc(sizeof(unsigned char));
		*item =  tree->item;
		
		put(ht, item, value);
	} 
	else 
	{
		code[depth] = '0';
		code[depth + 1] = '\0';
		mapping(tree->left, ht, code, depth + 1);
		code[depth] = '1';
		code[depth + 1] = '\0';
		mapping(tree->right, ht, code, depth + 1);
	} 
}
hash_table* tree_to_table(huffman_tree *tree)
{
	hash_table *ht = NULL;

	if(tree != NULL) 
	{
		ht = create_hash_table();
		//nota-se que a altura maxima da arvore é na base 2 log(2^13) = 13//
		unsigned char code[15] = "0";
		mapping(tree, ht, code, 0);
	}

	return ht;
}

unsigned char *string = NULL;
void traversal_pre_order(huffman_tree *tree, short int *id)
{
	if(tree != NULL)
	{
		if(isleaf(tree) && (tree->item == 42 || tree->item == 92) )
		{
			string[*id] = '\\';
			*id += 1;
		}

		string[*id] = tree->item;
		*id += 1 ;
		traversal_pre_order(tree->left, id);
		traversal_pre_order(tree->right, id);
	}
}
unsigned char* traversal_tree(huffman_tree *tree, short int *id)
{
	if(tree != NULL) 
	{
		/*tamanho maximo da árvore é 2^13 = 8192*/
		string = (unsigned char *) malloc(8300*sizeof(char));
		*id = 0;
		traversal_pre_order(tree, id);
	}
	return string;
}