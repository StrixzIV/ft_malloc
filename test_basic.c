/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:52:55 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/11/17 14:53:48 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "./includes/ft_malloc.h"

int main()
{
	char	*tiny_ptr;
	char	*small_ptr;
	char	*large_ptr;
	char	*re_ptr;

	printf("\n=== TEST 1: BASIC MALLOC/FREE/REALLOC ===\n\n");

	// --- Initial State ---
	ft_putstr_fd("--- Initial State ---\n", 1);
	show_alloc_mem();
	ft_putstr_fd("\n", 1);

	// --- Test 1: Malloc and Free ---
	ft_putstr_fd("--- Test 1.1: Malloc & Free ---\n", 1);
	ft_putstr_fd("Allocating tiny (32), small (512), large (8192)\n", 1);
	
	tiny_ptr = (char *)malloc(32);
	small_ptr = (char *)malloc(512);
	large_ptr = (char *)malloc(8192);

	if (!tiny_ptr || !small_ptr || !large_ptr) {
		ft_putstr_fd("ERROR: malloc failed\n", 2);
		return 1;
	}

	strcpy(tiny_ptr, "Hello Tiny");
	strcpy(small_ptr, "Hello Small");
	strcpy(large_ptr, "Hello Large");

	ft_putstr_fd("\nAfter allocation:\n", 1);
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
	ft_putstr_fd("--- Test 1.2: Realloc ---\n", 1);
	ft_putstr_fd("Allocating 100 bytes\n", 1);
	re_ptr = (char *)malloc(100);
	if (!re_ptr) {
		ft_putstr_fd("ERROR: malloc failed\n", 2);
		return 1;
	}
	strcpy(re_ptr, "Test data");
	show_alloc_mem();

	ft_putstr_fd("\nRealloc: growing to 1000 bytes (small)\n", 1);
	re_ptr = (char *)realloc(re_ptr, 1000);
	if (!re_ptr) {
		ft_putstr_fd("ERROR: realloc failed\n", 2);
		return 1;
	}
	show_alloc_mem();
	
	ft_putstr_fd("\nRealloc: growing to 10000 bytes (large)\n", 1);
	re_ptr = (char *)realloc(re_ptr, 10000);
	if (!re_ptr) {
		ft_putstr_fd("ERROR: realloc failed\n", 2);
		return 1;
	}
	show_alloc_mem();

	ft_putstr_fd("\nRealloc: shrinking to 20 bytes (tiny)\n", 1);
	re_ptr = (char *)realloc(re_ptr, 20);
	if (!re_ptr) {
		ft_putstr_fd("ERROR: realloc failed\n", 2);
		return 1;
	}
	show_alloc_mem();
	
	ft_putstr_fd("\nFreeing realloc'd block\n", 1);
	free(re_ptr);
	re_ptr = NULL;
	show_alloc_mem();

	printf("\n=== TEST 1: PASSED ===\n\n");
	return 0;
}
