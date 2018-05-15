#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/huffman_tree.h"
#include "../headers/hash_table.h"
#include "../headers/decompress.h"
#include "../headers/compress.h"
#define MAX_SIZE 256

unsigned char hash_function(void *key)
{
	return (*((unsigned char*) key))%MAX_SIZE;
}
int compare(void* key1,void* key2)
{
	return *((char*) key1) == *((char*) key2);
}
hash_table* create_hash_table()
{
	hash_table *ht = (hash_table*) malloc(sizeof(hash_table));
	int i;
	
	for(i=0; i<MAX_SIZE; i++)
		ht->table[i] = NULL;

	return ht;
}
void put(hash_table *ht, void *key, void *value)
{
	int h = hash_function(key);
	int count = 0;
	
	while(ht->table[h] != NULL && count < MAX_SIZE)
	{
		h = ( h + 1 ) % MAX_SIZE;
		count++;
	}
	if(ht->table[h] == NULL)
	{
		node *new_element = (node*) malloc(sizeof(node));
		new_element->key = key;
		new_element->value = value;
		ht->table[h] = new_element;
	}
}
void* get(hash_table *ht, void *key)
{
	int h = hash_function(key);

	int count = 0;
	while(ht->table[h] != NULL && count < MAX_SIZE)
	{
		if( compare(ht->table[h]->key, key) ) return (unsigned char*)ht->table[h]->value;

		h = ( h + 1 ) % MAX_SIZE;
		count++;
	}
	return NULL;
}
