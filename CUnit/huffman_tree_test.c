#include "../src/huffman_tree.c"
#include "CUnit/Basic.h"

unsigned char pq_item(queue *pq)
{
	return pq->head->item;
}

void create_node_of_huffman_tree_test()
{
		unsigned char *i = (unsigned char*) malloc(sizeof(unsigned char));
		*i = 16;
		huffman_tree *new_node = create_node_of_huffman_tree(*i, 5, NULL, NULL);
		
		if(new_node == NULL)
		{
			CU_FAIL("Node wasn't correctly created");
		} 
		else 
		{
			CU_PASS("OK");		
		}	
}

void enqueue_test()
{
	queue *pq = create_priority_queue();
	huffman_tree *test_node = (huffman_tree*) malloc(sizeof(huffman_tree));
	unsigned char *c = (unsigned char*) malloc(sizeof(unsigned char));

	for(int j=12; j>0; j--)
	{
		*c = 65+j;
		test_node = create_node_of_huffman_tree(*c, j, NULL, NULL);
		enqueue(pq, test_node);
	}

	for(int i=0; i<12; i++)
	{
		if(i==0)
		{
			CU_ASSERT_EQUAL(pq_item(pq), 'B');
		}
		if(i==3)
		{
			CU_ASSERT_EQUAL(pq_item(pq), 'E');
		}
		if(i==6)
		{
			CU_ASSERT_EQUAL(pq_item(pq), 'H');
		}
		if(i==7)
		{
			CU_ASSERT_EQUAL(pq_item(pq), 'I');
		}
		if(i==9)
		{
			CU_ASSERT_EQUAL(pq_item(pq), 'K');
		}
		pq->head = pq->head->next;
	}
}

void dequeue_test()
{
	queue *pq = create_priority_queue();
	huffman_tree *test_node = (huffman_tree*) malloc(sizeof(huffman_tree));
	unsigned char *c = (unsigned char*) malloc(sizeof(unsigned char));

	for(int j=12; j>0; j--)
	{
		*c = 65+j;
		test_node = create_node_of_huffman_tree(*c, j, NULL, NULL);
		enqueue(pq, test_node);
	}

	*c = pq->head->item;//Gets the first in the Queue
	test_node = dequeue(pq);//Gets the dequeued
	if(test_node->item == *c)
	{
		CU_PASS("OK");	
	} 
	else 
	{
		CU_FAIL("Node wasn't correctly dequeued");	
	}
}

void read_bits_test()
{
	int file_source_size;
	unsigned char c;
	int* table = (int*) malloc(sizeof(int)*256);
	FILE *file_source = fopen("read_bits_test.txt","rb");
	memset(table,0,sizeof(int)*256);

	fseek(file_source,0,SEEK_END);
	file_source_size = ftell(file_source);
	fseek(file_source,0,SEEK_SET);	

	table = read_bits(file_source,file_source_size);
	
	c = 'A';
	if(table[c] == 6)
	{
		CU_PASS("OK");	
	} 
	else 
	{
		CU_FAIL("Table with frequency failed");	
	}
	c = 'D';
	if(table[c] == 3)
	{
		CU_PASS("OK");	
	} 
	else 
	{
		CU_FAIL("Table with frequency failed");	
	}
	c = 'F';
	if(table[c] == 1)
	{
		CU_PASS("OK");	
	} 
	else 
	{
		CU_FAIL("Table with frequency failed");	
	}

	free(table);

	//PS: Table is an array with the frequency
}

void create_huffman_queue_test()
{
	int file_source_size;
	unsigned char c;
	huffman_tree *test_node = (huffman_tree*) malloc(sizeof(huffman_tree));
	int* table = (int*) malloc(sizeof(int)*256);
	queue *pq = create_priority_queue();
	FILE *file_source = fopen("read_bits_test.txt","rb");
	memset(table,0,sizeof(int)*256);

	fseek(file_source,0,SEEK_END);
	file_source_size = ftell(file_source);
	fseek(file_source,0,SEEK_SET);	

	table = read_bits(file_source,file_source_size);

	CU_ASSERT_EQUAL(dequeue(pq), NULL);
	pq = create_huffman_queue(table);

	test_node = dequeue(pq);
	if(test_node->item == 'F')
	{
		CU_PASS("OK");
	}
	else
	{
		CU_FAIL("Error in creating priority queue from frequency table");
	}
	test_node = dequeue(pq);
	if(test_node->item == 'E')
	{
		CU_PASS("OK");
	}
	else
	{
		CU_FAIL("Error in creating priority queue from frequency table");
	}
	test_node = dequeue(pq);
	if(test_node->item == 'D')
	{
		CU_PASS("OK");
	}
	else
	{
		CU_FAIL("Error in creating priority queue from frequency table");
	}
}

void create_huffman_tree_test()
{
	int file_source_size;
	unsigned char c;
	huffman_tree *ht = (huffman_tree*) malloc(sizeof(huffman_tree));
	int* table = (int*) malloc(sizeof(int)*256);
	queue *pq = create_priority_queue();
	FILE *file_source = fopen("read_bits_test.txt","rb");
	memset(table,0,sizeof(int)*256);

	fseek(file_source,0,SEEK_END);
	file_source_size = ftell(file_source);
	fseek(file_source,0,SEEK_SET);	

	table = read_bits(file_source,file_source_size);
	pq = create_huffman_queue(table);
	ht = create_huffman_tree(pq);

	if(ht->left->item == '*')
	{
		CU_PASS("OK");
	}
	else
	{
		CU_FAIL("Huffman Tree creation failed");
	}
	if(ht->left->left->item == 'C')
	{
		CU_PASS("OK");
	}
	else
	{
		CU_FAIL("Huffman Tree creation failed");
	}
	if(ht->left->right->item == 'B')
	{
		CU_PASS("OK");
	}
	else
	{
		CU_FAIL("Huffman Tree creation failed");
	}
	if(ht->right->right->item == 'A')
	{
		CU_PASS("OK");
	}
	else
	{
		CU_FAIL("Huffman Tree creation failed");
	}
}

void build_huffman_tree_test()
{
	huffman_tree *ht = (huffman_tree*) malloc(sizeof(huffman_tree));
	FILE *file = fopen("build_huffman_tree_test.txt","rb");

	ht = build_huffman_tree(ht,file);

	if(ht->left->item == '*')
	{
		CU_PASS("OK");
	}
	else
	{
		CU_FAIL("Huffman Tree building failed");
	}
	if(ht->left->left->item == 'C')
	{
		CU_PASS("OK");
	}
	else
	{
		CU_FAIL("Huffman Tree building failed");
	}
	if(ht->left->right->item == 'B')
	{
		CU_PASS("OK");
	}
	else
	{
		CU_FAIL("Huffman Tree building failed");
	}
	if(ht->right->right->item == 'A')
	{
		CU_PASS("OK");
	}
	else
	{
		CU_FAIL("Huffman Tree building failed");
	}
	fclose(file);
}

void put_tree_on_file_test()
{
	FILE *file_destination = fopen("put_tree_on_file_test.txt","wb");
	huffman_tree *ht = (huffman_tree*)malloc(sizeof(huffman_tree));
	unsigned char ast = '*';
	unsigned char c = 'C';
	unsigned char b = 'B';
	unsigned char d = 'D';
	ht = create_node_of_huffman_tree(ast,0,create_node_of_huffman_tree(ast,0,create_node_of_huffman_tree(c,0,NULL,NULL),create_node_of_huffman_tree(b,0,NULL,NULL)),create_node_of_huffman_tree(d,0,NULL,NULL));
	fseek(file_destination,0,SEEK_SET);
	put_tree_on_file(ht,file_destination);
	fclose(file_destination);
	FILE *file = fopen("put_tree_on_file_test.txt","rb");
	c = getc(file);
	if(c == '*')
	{
		CU_PASS("OK");
	}
	else
	{
		CU_FAIL("put_tree_on_file function with error");
	}
	c = getc(file);
	if(c == '*')
	{
		CU_PASS("OK");
	}
	else
	{
		CU_FAIL("put_tree_on_file function with error");
	}
	c = getc(file);
	if(c == 'C')
	{
		CU_PASS("OK");
	}
	else
	{
		CU_FAIL("put_tree_on_file function with error");
	}
	c = getc(file);
	if(c == 'B')
	{
		CU_PASS("OK");
	}
	else
	{
		CU_FAIL("put_tree_on_file function with error");
	}
	c = getc(file);
	if(c == 'D')
	{
		CU_PASS("OK");
	}
	else
	{
		CU_FAIL("put_tree_on_file function with error");
	}
}

void maximum_bits_number_test()
{
	//Building a tree to test	
	FILE *file1 = fopen("maximum_bits_number_test.txt","rb");
	huffman_tree *ht = (huffman_tree*) malloc(sizeof(huffman_tree));
	ht = build_huffman_tree(ht,file1);
	//Test begin
	CU_ASSERT_EQUAL(maximum_bits_number(ht),4);
}

void tree_size_test()
{
	//Building a tree to test
	FILE *file1 = fopen("maximum_bits_number_test.txt","rb");
	huffman_tree *ht = (huffman_tree*) malloc(sizeof(huffman_tree));
	ht = build_huffman_tree(ht,file1);
	//Test begin
	CU_ASSERT_EQUAL(tree_size(ht),11);
}

int main() {

   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

  	CU_pSuite pSuite = NULL;

	pSuite = CU_add_suite("huffman_tree_test_suite", 0, 0);

	if (NULL == pSuite) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}

	// Add the test to the suite
	if (NULL == CU_add_test(pSuite, "create_node_of_huffman_tree_test", create_node_of_huffman_tree_test)) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite, "enqueue_test", enqueue_test)) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite, "dequeue_test", dequeue_test)) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite, "read_bits_test", read_bits_test)) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite, "create_huffman_queue_test", create_huffman_queue_test)) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite, "create_huffman_tree_test", create_huffman_tree_test)) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite, "put_tree_on_file_test", put_tree_on_file_test)) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite, "build_huffman_tree_test", build_huffman_tree_test)) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite, "maximum_bits_number_test", maximum_bits_number_test)) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite, "tree_size_test", tree_size_test)) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}


   CU_basic_set_mode(CU_BRM_VERBOSE);

   CU_basic_run_tests();
   return CU_get_error();
}
