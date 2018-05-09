#include "../headers/decompress.h"

int is_bit_i_set(unsigned char c, int i)
{
	unsigned char mask = 1 << i;
	return mask & c;
}
int trash_length(FILE *file_src)
{
	fseek(file_src, 0, SEEK_SET);
	unsigned char c;
	c = getc(file_src);
	return c >> 5;
}

int tree_length(FILE *file_src)
{
	fseek(file_src, 0, SEEK_SET);

	unsigned char byte1 = getc(file_src);
	unsigned char byte2 = getc(file_src);
	short int size = 0;

	byte1 = byte1 << 3;
	byte1 = byte1 >> 3;
	size = byte1;
	size = size << 8;
	size = byte2 | size;

	return size;
}

void write_the_decompressed_file(huffman_tree* ht,FILE* file_src,FILE* file_dtn)
{
	unsigned char c;
	int aux_trash = 0;
	int trash = trash_length(file_src);
	int file_size,i,j;
	int tree_size = tree_length(file_src);
	huffman_tree* aux_ht;

	fseek(file_src,0,SEEK_END);

	file_size = ftell(file_src) - 2 - tree_size;

	fseek(file_src,(2 + tree_size),SEEK_SET);

	aux_ht = ht;
	for(i = 0; i < file_size;++i)
	{
		if(i == file_size - 1)
			aux_trash = trash;

		c = getc(file_src);

		for(j = 7;j >= aux_trash;--j)
		{
			if(!is_bit_i_set(c,j))	aux_ht = aux_ht->left;
					
			if(is_bit_i_set(c,j))	aux_ht = aux_ht->right;

			if(isleaf(aux_ht))
			{
				fprintf(file_dtn,"%c", aux_ht->item);
				aux_ht = ht;			
			}
		}
	}

	fseek(file_src,0,SEEK_SET);
	fseek(file_dtn,0,SEEK_SET);
	fclose(file_dtn);
	fclose(file_src);
}
void decompress(FILE *file_src,FILE *file_dtn)
{
	printf("Wait, decompression is intializing\n");
	huffman_tree *ht;
	fseek(file_src,2,SEEK_SET);
	ht = build_huffman_tree(ht,file_src);
	write_the_decompressed_file(ht,file_src,file_dtn);
	printf("Thanks for waiting, your file was successfully decompressed");
}
