#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/huffman_tree.h"
#include "../headers/hash_table.h"
#include "../headers/decompress.h"
#include "../headers/compress.h"

unsigned char set_bit(unsigned char c, int k,int i)
{
	unsigned char mask = k << i;
	return mask | c;
}
void set_header(FILE *new_file, short int tree_size, unsigned char trash)
{
	unsigned char byte = tree_size >> 8;
	trash = trash | byte;
	fprintf(new_file, "%c", trash);
	byte = tree_size;
	fprintf(new_file, "%c", byte);
}
void set_tree(FILE *new_file, unsigned char *string_tree, short int size)
{
	int i;
	for(i = 0; i < size; ++i)
	{
	 	fprintf(new_file,"%c", string_tree[i]);
	}
}
void write_the_compressed_file(FILE *file_src, FILE *file_dtn, hash_table *hash, int file_size, huffman_tree *tree)
{
	int i, j, pos;
	unsigned char byte = 0, trash;
	unsigned char *current, *string_tree;

	// SALVA OS DOIS PRIMEIROS BYTES NO ARQUIVO
	fprintf(file_dtn,"%c", byte);
	fprintf(file_dtn,"%c", byte);

	short int *tree_size = (short int *) malloc(sizeof(short int));
	
	string_tree = traversal_tree(tree, tree_size); //Ponteiro para uma string que contem a arvore em pre ordem
	set_tree(file_dtn, string_tree, *tree_size); //Coloca a arvore em pre ordem no arquivo
	unsigned char *aux = (unsigned char*) malloc(sizeof(unsigned char));

	pos = 0;
	for(i = 0; i < file_size; ++i)
	{
		*aux = getc(file_src);
		current = (unsigned char*) get(hash, aux);
		j = 0;
		while( current[j] != '\0')
		{
			if(pos >= 8)
			{
				fprintf(file_dtn,"%c", byte);
				byte = 0;
				pos = 0;	
			}

			if(current[j] == '1')	byte = set_bit(byte,1,7 - pos);	
			++pos;
			++j;
		}
	}
	fprintf(file_dtn, "%c", byte);
	fseek(file_dtn, 0, SEEK_SET);

	trash = (8-pos) << 5;
	set_header(file_dtn, *tree_size, trash);
	free(tree_size);

	fseek(file_dtn, 0, SEEK_SET);
	fseek(file_src,0,SEEK_SET);
	fclose(file_src);
	fclose(file_dtn);

}
void compress(FILE* file_src,int file_size,FILE* file_dtn)
{ 	
	printf("Wait, your file is being compressed\n");

	int* table = read_bits(file_src,file_size);
	queue* pq = create_huffman_queue(table);
	huffman_tree* ht = create_huffman_tree(pq);
	
	hash_table *dictionary = tree_to_table(ht);
  
	write_the_compressed_file(file_src,file_dtn,dictionary,file_size,ht);//retorna o tamanho do lixo

	printf("Thanks for waiting your file was successfully compressed");
}