#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#define MAX_SIZE 256


/*
 * Create a hash table
 */
hash_table* create_hash_table();

/*
 * Receives key data,the value and dispersion function
 * Put a new element on this table
 */
void put(hash_table *ht, void *key, void *value);

/*
 * Receives key data,the dispersion function and comparation function
 * search for an element in the table and returns its value
 */
void* get(hash_table *ht, void *key);

#endif
