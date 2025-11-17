/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_edge_cases.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:55:55 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/11/17 14:56:16 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_malloc.h"
#include <string.h>
#include <stdio.h>

int main() {
    
	char *ptr1, *ptr2, *ptr3;

	printf("\n=== TEST 2: EDGE CASES ===\n\n");

	// Test malloc(0)
	ft_putstr_fd("--- Test 2.1: malloc(0) ---\n", 1);
	ptr1 = (char *)malloc(0);
	if (ptr1 == NULL) {
		ft_putstr_fd("✓ malloc(0) correctly returned NULL\n", 1);
	} else {
		ft_putstr_fd("✗ ERROR: malloc(0) should return NULL\n", 2);
		free(ptr1);
	}
	ft_putstr_fd("\n", 1);

	// Test free(NULL)
	ft_putstr_fd("--- Test 2.2: free(NULL) ---\n", 1);
	free(NULL);
	ft_putstr_fd("✓ free(NULL) completed without crash\n", 1);
	ft_putstr_fd("\n", 1);

	// Test realloc(NULL, size) - should behave like malloc(size)
	ft_putstr_fd("--- Test 2.3: realloc(NULL, 50) ---\n", 1);
	ptr1 = (char *)realloc(NULL, 50);
	if (ptr1) {
		ft_putstr_fd("✓ realloc(NULL, 50) acts like malloc(50)\n", 1);
		strcpy(ptr1, "Allocated via realloc");
		show_alloc_mem();
	} else {
		ft_putstr_fd("✗ ERROR: realloc(NULL, 50) failed\n", 2);
	}
	ft_putstr_fd("\n", 1);

	// Test realloc(ptr, 0) - should behave like free(ptr)
	ft_putstr_fd("--- Test 2.4: realloc(ptr, 0) ---\n", 1);
	ptr2 = (char *)realloc(ptr1, 0);
	if (ptr2 == NULL) {
		ft_putstr_fd("✓ realloc(ptr, 0) correctly returned NULL\n", 1);
	} else {
		ft_putstr_fd("✗ ERROR: realloc(ptr, 0) should return NULL\n", 2);
	}
	show_alloc_mem();
	ft_putstr_fd("\n", 1);

	// Test double free detection (if MALLOC_CHECK is enabled)
	ft_putstr_fd("--- Test 2.5: Double free (enable MALLOC_CHECK) ---\n", 1);
	ptr1 = (char *)malloc(100);
	if (ptr1) {
		free(ptr1);
		ft_putstr_fd("First free completed\n", 1);
		ft_putstr_fd("Attempting double free (should be caught with MALLOC_CHECK):\n", 1);
		free(ptr1); // This should be caught if MALLOC_CHECK is enabled
	}
	ft_putstr_fd("\n", 1);

	// Test very large allocation
	ft_putstr_fd("--- Test 2.6: Very large allocation (1MB) ---\n", 1);
	ptr1 = (char *)malloc(1024 * 1024);
	if (ptr1) {
		ft_putstr_fd("✓ 1MB allocation successful\n", 1);
		memset(ptr1, 'A', 1024 * 1024);
		show_alloc_mem();
		free(ptr1);
	} else {
		ft_putstr_fd("✗ ERROR: 1MB allocation failed\n", 2);
	}
	ft_putstr_fd("\n", 1);

	// Test boundary sizes
	ft_putstr_fd("--- Test 2.7: Boundary sizes ---\n", 1);
	ptr1 = (char *)malloc(1);        // Minimum
	ptr2 = (char *)malloc(256);      // TINY boundary
	ptr3 = (char *)malloc(2048);     // SMALL boundary
	
	if (ptr1 && ptr2 && ptr3) {
		ft_putstr_fd("✓ All boundary allocations successful\n", 1);
		show_alloc_mem();
		free(ptr1);
		free(ptr2);
		free(ptr3);
	} else {
		ft_putstr_fd("✗ ERROR: Boundary allocation failed\n", 2);
	}
	ft_putstr_fd("\n", 1);

	// Test realloc with same size
	ft_putstr_fd("--- Test 2.8: realloc with same size ---\n", 1);
	ptr1 = (char *)malloc(100);
	if (ptr1) {
		strcpy(ptr1, "Original data");
		char *old_ptr = ptr1;
		ptr1 = (char *)realloc(ptr1, 100);
		if (ptr1 == old_ptr) {
			ft_putstr_fd("✓ realloc same size returned same pointer\n", 1);
		} else if (ptr1) {
			ft_putstr_fd("✓ realloc same size returned different pointer (acceptable)\n", 1);
		}
		if (ptr1 && strcmp(ptr1, "Original data") == 0) {
			ft_putstr_fd("✓ Data preserved after realloc\n", 1);
		}
		free(ptr1);
	}

	printf("\n=== TEST 2: PASSED ===\n\n");
	return 0;

}