/*
** This is a simple test program for your ft_malloc library.
*/

#include "./includes/ft_malloc.h"
#include <string.h>


int main()
{
	char	*tiny_ptr;
	char	*small_ptr;
	char	*large_ptr;
	char	*re_ptr;

	ft_putstr_fd("--- Initial State ---\n", 1);
	show_alloc_mem();
	ft_putstr_fd("\n", 1);

	// --- Test 1: Malloc and Free ---
	ft_putstr_fd("--- Test 1: Malloc & Free ---\n", 1);
	ft_putstr_fd("Allocating tiny (32), small (512), large (8192)\n", 1);
	
	tiny_ptr = (char *)malloc(32);
	small_ptr = (char *)malloc(512);
	large_ptr = (char *)malloc(8192);

	if (tiny_ptr) strcpy(tiny_ptr, "Hello Tiny");
	if (small_ptr) strcpy(small_ptr, "Hello Small");
	if (large_ptr) strcpy(large_ptr, "Hello Large");

    ft_putstr_fd("\n--- EXTENDED VIEW ---\n", 1);
	show_alloc_mem_ex();

	show_alloc_mem();
	ft_putstr_fd("\nFreeing small block\n", 1);
	free(small_ptr);
	small_ptr = NULL;
	show_alloc_mem();
	
	ft_putstr_fd("\nFreeing tiny and large blocks\n", 1);
	free(tiny_ptr);
	free(large_ptr);
	tiny_ptr = NULL;
	large_ptr = NULL;
	
	ft_putstr_fd("--- After all frees ---\n", 1);
	show_alloc_mem();
	ft_putstr_fd("\n", 1);

	// --- Test 2: Realloc ---
	ft_putstr_fd("--- Test 2: Realloc ---\n", 1);
	ft_putstr_fd("Allocating 100 bytes\n", 1);
	re_ptr = (char *)malloc(100);
	if (re_ptr) strcpy(re_ptr, "Test data");
	show_alloc_mem();

	ft_putstr_fd("\nRealloc: growing to 1000 bytes (small)\n", 1);
	re_ptr = (char *)realloc(re_ptr, 1000);
	show_alloc_mem();
	
	ft_putstr_fd("\nRealloc: growing to 10000 bytes (large)\n", 1);
	re_ptr = (char *)realloc(re_ptr, 10000);
	show_alloc_mem();

	ft_putstr_fd("\nRealloc: shrinking to 20 bytes (tiny)\n", 1);
	re_ptr = (char *)realloc(re_ptr, 20);
	show_alloc_mem();
	
	ft_putstr_fd("\nFreeing realloc'd block\n", 1);
	free(re_ptr);
	re_ptr = NULL;
	show_alloc_mem();

	// --- Test 3: Edge Cases ---
	ft_putstr_fd("\n--- Test 3: Edge Cases ---\n", 1);
	ft_putstr_fd("Testing realloc(NULL, 50)...\n", 1);
	char *re_null = (char *)realloc(NULL, 50); // Should act like malloc(50)
	show_alloc_mem();

	ft_putstr_fd("\nTesting realloc(ptr, 0)...\n", 1);
	re_null = (char *)realloc(re_null, 0); // Should act like free(re_null)
	if (re_null != NULL)
		ft_putstr_fd("ERROR: realloc(ptr, 0) did not return NULL\n", 2);
	
	show_alloc_mem();
	ft_putstr_fd("\n--- Test Complete ---\n", 1);

	return (0);
}
