#include "CUnit/Basic.h"
#include "../src/decompress.c"
#include "../src/huffman_tree.c"
#include <stdio.h>

void generate_header(FILE *file_destination, unsigned char trash, short int tree_size)
{
	unsigned char header = tree_size >> 8;
	trash = trash << 5;
	trash = trash | header;
	fprintf(file_destination, "%c", trash);
	header = tree_size;
	fprintf(file_destination, "%c", header);
}

void trash_length_test()
{
	unsigned char trash = 4;
	short int tree_size = 21;
	int trash_return;
	FILE *file = fopen("header_test.txt", "wb");
	fseek(file,0,SEEK_SET);
	if(file == NULL) CU_FAIL("trash_length test 2 failed");
	generate_header(file,trash,tree_size);//Writes the header in the file
	fclose(file);//Now, we closed to reopen it after and make the tests
	file = fopen("header_test.txt", "rb");
	
	CU_ASSERT_EQUAL(trash_length(file),4);
}

void tree_length_test()
{
	unsigned char trash = 4;
	short int tree_size = 21;
	int trash_return;
	FILE *file = fopen("header_test.txt", "wb");
	fseek(file,0,SEEK_SET);
	if(file == NULL) CU_FAIL("trash_length test 2 failed");
	generate_header(file,trash,tree_size);//Writes the header in the file
	fclose(file);//Now, we closed to reopen it after and make the tests
	file = fopen("header_test.txt", "rb");

	CU_ASSERT_EQUAL(tree_length(file),21);
}

void write_the_decompressed_file_test()
{
	FILE *compressed = fopen("compressed_file_test1","rb");
	FILE *decompressed = fopen("write_the_decompressed_file_test","wb");
	fseek(compressed,2,SEEK_SET);
	huffman_tree *ht;
	ht = build_huffman_tree(ht,compressed);
	write_the_decompressed_file(ht,compressed,decompressed);
	decompressed = fopen("write_the_decompressed_file_test","rb");
	fseek(decompressed,0,SEEK_SET);
	CU_ASSERT_EQUAL(getc(decompressed),'A');
	CU_ASSERT_EQUAL(getc(decompressed),'A');
	CU_ASSERT_EQUAL(getc(decompressed),'A');
	fseek(decompressed,6,SEEK_SET);
	CU_ASSERT_EQUAL(getc(decompressed),'B');
	fseek(decompressed,11,SEEK_SET);
	CU_ASSERT_EQUAL(getc(decompressed),'C');
	fseek(decompressed,15,SEEK_SET);
	CU_ASSERT_EQUAL(getc(decompressed),'D');
	fseek(decompressed,18,SEEK_SET);
	CU_ASSERT_EQUAL(getc(decompressed),'E');
	CU_ASSERT_EQUAL(getc(decompressed),'E');
	CU_ASSERT_EQUAL(getc(decompressed),'F');
}

int main()
{
	if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

  	CU_pSuite pSuite = NULL;

	pSuite = CU_add_suite("huffman_tree_test_suite", 0, 0);

	if (NULL == pSuite) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}

	//Add tests to the suite
	if (NULL == CU_add_test(pSuite, "trash_length_test", trash_length_test)) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite, "tree_length_test", tree_length_test)) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite, "write_the_decompressed_file_test", write_the_decompressed_file_test)) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);

   CU_basic_run_tests();
   return CU_get_error();
}
