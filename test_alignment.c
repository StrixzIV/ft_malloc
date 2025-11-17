/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_alignment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:57:24 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/11/17 14:57:25 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_malloc.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

int main()
{
	printf("\n=== TEST 4: MEMORY ALIGNMENT ===\n\n");

	ft_putstr_fd("--- Test 4.1: Check 16-byte alignment ---\n", 1);
	
	// Test various sizes
	size_t sizes[] = {1, 8, 16, 32, 64, 100, 256, 512, 1000, 2048, 4096};
	int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
	int all_aligned = 1;
	
	for (int i = 0; i < num_sizes; i++) {
		void *ptr = malloc(sizes[i]);
		if (!ptr) {
			printf("ERROR: malloc(%zu) failed\n", sizes[i]);
			continue;
		}
		
		uintptr_t addr = (uintptr_t)ptr;
		if (addr % 16 != 0) {
			printf("✗ ERROR: malloc(%zu) returned unaligned pointer: %p (mod 16 = %lu)\n",
				   sizes[i], ptr, addr % 16);
			all_aligned = 0;
		} else {
			printf("✓ malloc(%zu) -> %p (aligned)\n", sizes[i], ptr);
		}
		
		free(ptr);
	}
	
	if (all_aligned) {
		ft_putstr_fd("\n✓ All allocations are properly aligned to 16 bytes\n", 1);
	} else {
		ft_putstr_fd("\n✗ Some allocations were not aligned!\n", 2);
	}
	ft_putstr_fd("\n", 1);

	// Test alignment after realloc
	ft_putstr_fd("--- Test 4.2: Alignment after realloc ---\n", 1);
	void *ptr = malloc(32);
	if (ptr) {
		printf("Original pointer: %p\n", ptr);
		ptr = realloc(ptr, 128);
		if (ptr) {
			uintptr_t addr = (uintptr_t)ptr;
			printf("After realloc: %p\n", ptr);
			if (addr % 16 == 0) {
				ft_putstr_fd("✓ Pointer still aligned after realloc\n", 1);
			} else {
				ft_putstr_fd("✗ ERROR: Pointer lost alignment after realloc\n", 2);
			}
			free(ptr);
		}
	}

	printf("\n=== TEST 4: PASSED ===\n\n");
	return 0;
}
