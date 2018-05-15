#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/huffman_tree.h"
#include "headers/hash_table.h"
#include "headers/decompress.h"
#include "headers/compress.h"


int main()
{
	char src_file_name[300];
	char dtn_file_name[300];
	char c;
	int file_size;
	FILE* file_src;
	FILE* file_dtn;
	
	printf("Welcome to Huffman File Compressor, please, type 'c' for compressing, 'd' for decompressing or type anything different to exit program\n\n >");

	scanf("%c",&c);
	if(c == 'c' || c == 'C')
	{	
		printf("Ok, you want to compress, please, type the name of the file to compress\n\n >");
  	}
  	else if(c == 'd' || c == 'D')
  	{
  		printf("Ok, you want to decompress, please, type de name of the file to decompress\n\n >");
  	}
  	else
  	{
  		return 0;
  	}
  	scanf("%s", src_file_name);
  	printf("Now, we need an destination file\n\n >");
  	scanf("%s", dtn_file_name);	


  	if(c == 'c' || c == 'C')
  	{	
  		file_src = fopen(src_file_name,"rb");

  		if(file_src == NULL)
		{
			printf("The source file could not be opened\n");
			return 0;
		}
		file_dtn = fopen(dtn_file_name,"wb");
		strcat(dtn_file_name,".huff");
		if(file_dtn == NULL)
		{
			printf("The destination file could not be opened\n");
			return 0;
		}

		fseek(file_src, 0, SEEK_END);
	  	file_size = ftell(file_src);
	  	fseek(file_src, 0, SEEK_SET);


		compress(file_src,file_size,file_dtn);
	}
	else if(c == 'd' || c == 'D')
	{
		file_src = fopen(src_file_name,"rb");

  		if(file_src == NULL)
		{
			printf("The source file could not be opened\n");
			return 0;
		}
		file_dtn = fopen(dtn_file_name,"wb");
		if(file_dtn == NULL)
		{
			printf("The destination file could not be opened\n");
			return 0;
		}
		decompress(file_src,file_dtn);
	}
}