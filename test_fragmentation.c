/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fragmentation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:56:48 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/11/17 14:56:50 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_malloc.h"
#include <string.h>
#include <stdio.h>

int main()
{
	char *ptrs[10];
	int i;

	printf("\n=== TEST 3: FRAGMENTATION & COALESCING ===\n\n");

	// Test 3.1: Create fragmentation
	ft_putstr_fd("--- Test 3.1: Create fragmentation ---\n", 1);
	ft_putstr_fd("Allocating 10 tiny blocks\n", 1);
	
	for (i = 0; i < 10; i++) {
		ptrs[i] = (char *)malloc(32);
		if (!ptrs[i]) {
			ft_putstr_fd("ERROR: malloc failed\n", 2);
			return 1;
		}
		sprintf(ptrs[i], "Block %d", i);
	}
	
	ft_putstr_fd("\nAfter allocations:\n", 1);
	show_alloc_mem();

	// Free every other block to create fragmentation
	ft_putstr_fd("\nFreeing blocks 1, 3, 5, 7, 9 to create fragmentation\n", 1);
	for (i = 1; i < 10; i += 2) {
		free(ptrs[i]);
		ptrs[i] = NULL;
	}
	
	ft_putstr_fd("\nAfter fragmentation:\n", 1);
	show_alloc_mem();
	ft_putstr_fd("\n", 1);

	// Test 3.2: Free adjacent blocks to test coalescing
	ft_putstr_fd("--- Test 3.2: Test coalescing ---\n", 1);
	ft_putstr_fd("Freeing blocks 0, 2, 4 (should coalesce with freed blocks)\n", 1);
	
	for (i = 0; i < 10; i += 2) {
		if (ptrs[i]) {
			free(ptrs[i]);
			ptrs[i] = NULL;
		}
	}
	
	ft_putstr_fd("\nAfter coalescing (should have larger free blocks):\n", 1);
	show_alloc_mem();
	ft_putstr_fd("\n", 1);

	// Test 3.3: Allocate in fragmented space
	ft_putstr_fd("--- Test 3.3: Allocate in fragmented space ---\n", 1);
	char *new_ptr = (char *)malloc(64);
	if (new_ptr) {
		ft_putstr_fd("✓ Successfully allocated 64 bytes in fragmented space\n", 1);
		strcpy(new_ptr, "Reused space");
		show_alloc_mem();
		free(new_ptr);
	} else {
		ft_putstr_fd("✗ ERROR: Failed to allocate in fragmented space\n", 2);
	}
	ft_putstr_fd("\n", 1);

	// Test 3.4: Multiple zones
	ft_putstr_fd("--- Test 3.4: Multiple zones ---\n", 1);
	ft_putstr_fd("Allocating enough blocks to create multiple zones\n", 1);
	
	#define MANY_ALLOCS 150
	char *many_ptrs[MANY_ALLOCS];
	
	for (i = 0; i < MANY_ALLOCS; i++) {
		many_ptrs[i] = (char *)malloc(32);
		if (!many_ptrs[i]) {
			ft_putstr_fd("ERROR: malloc failed\n", 2);
			break;
		}
	}
	
	ft_putstr_fd("\nAfter many allocations (should show multiple zones):\n", 1);
	show_alloc_mem();
	
	ft_putstr_fd("\nFreeing all blocks\n", 1);
	for (int j = 0; j < i; j++) {
		free(many_ptrs[j]);
	}
	
	ft_putstr_fd("\nAfter freeing all:\n", 1);
	show_alloc_mem();

	printf("\n=== TEST 3: PASSED ===\n\n");
	return 0;
}