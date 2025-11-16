/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <strixz.self@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 00:10:44 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/11/17 00:48:16 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

static void print_block_ex(t_block_metadata * head, size_t * total, int show_hex) {

	size_t used_block_count = 0;
	t_block_metadata * current = head;

	while (current != NULL) {
		used_block_count++;
		current = current->next;
	}

	t_block_metadata *stack_buffer[256];
	t_block_metadata **ptr_vector;
	void *mmap_ptr = NULL;

	if (used_block_count <= 256) {
		ptr_vector = stack_buffer;
	} else {
		size_t needed_size = used_block_count * sizeof(t_block_metadata *);
		size_t aligned_size = align_value(needed_size, PAGE_SIZE);
		
		mmap_ptr = allocate(NULL, aligned_size);
		if (mmap_ptr == MAP_FAILED)
			return;
		
		ptr_vector = (t_block_metadata **)mmap_ptr;
	}

	current = head;
	size_t index = 0;

	while (current != NULL)	{
		ptr_vector[index++] = current;
		current = current->next;
	}

	// Sort buffer by address
	sort((void **)ptr_vector, used_block_count);

	for (size_t i = 0; i < used_block_count; i++) {
		current = ptr_vector[i];
		void *buffer_addr = (void *)((char *)current + aligned_header_size());
		
		ft_putstr_fd("0x", 1);
		put_hex_fd((size_t)buffer_addr, 1);
		ft_putstr_fd(" - 0x", 1);
		put_hex_fd((size_t)buffer_addr + current->block_size, 1);
		ft_putstr_fd(" : ", 1);
		put_unbr_fd(current->block_size, 1);
		ft_putstr_fd(" bytes\n", 1);

		if (show_hex) {
			print_hex_dump(buffer_addr, current->block_size);
		}

		*total += current->block_size;

	}

	if (mmap_ptr != NULL) {
		size_t needed_size = used_block_count * sizeof(t_block_metadata *);
		size_t aligned_size = align_value(needed_size, PAGE_SIZE);
		munmap(mmap_ptr, aligned_size);
	}

}

static void print_zone_ex(t_zone_metadata * head, char * name, size_t * total, size_t *fragmentation, int show_hex) {

	size_t used_block_count = 0;
	t_zone_metadata * current = head;
	
	while (current != NULL) {
		used_block_count++;
		current = current->next;
	}

	t_zone_metadata *stack_buffer[256];
	t_zone_metadata **ptr_vector;
	void *mmap_ptr = NULL;

	if (used_block_count <= 256) {
		ptr_vector = stack_buffer;
	} else {
		size_t needed_size = used_block_count * sizeof(t_zone_metadata *);
		size_t aligned_size = align_value(needed_size, PAGE_SIZE);
		
		mmap_ptr = allocate(NULL, aligned_size);
		if (mmap_ptr == MAP_FAILED)
			return;
		
		ptr_vector = (t_zone_metadata **)mmap_ptr;
	}

	current = head;
	size_t index = 0;
	while (current != NULL) {
		ptr_vector[index++] = current;
		current = current->next;
	}

	// Sort buffer by address
	sort((void **)ptr_vector, used_block_count);

	for (size_t i = 0; i < used_block_count; i++) {

		current = ptr_vector[i];
		
		if (current->used_blocks == NULL) {
			continue;
		}
		
		ft_putstr_fd(name, 1);
		ft_putstr_fd(": 0x", 1);
		put_hex_fd((size_t)current, 1);
		ft_putstr_fd(" (zone size: ", 1);
		put_unbr_fd(current->allocated_size, 1);
		ft_putstr_fd(" bytes)\n", 1);

		size_t zone_fragmentation = 0;
		t_block_metadata *free_block = current->freed_blocks;

		while (free_block) {
			zone_fragmentation += free_block->block_size;
			free_block = free_block->next;
		}
		
		if (zone_fragmentation > 0) {
			ft_putstr_fd("Free space in zone: ", 1);
			put_unbr_fd(zone_fragmentation, 1);
			ft_putstr_fd(" bytes\n", 1);
			*fragmentation += zone_fragmentation;
		}

		print_block_ex(current->used_blocks, total, show_hex);

	}

	if (mmap_ptr != NULL) {
		size_t needed_size = used_block_count * sizeof(t_zone_metadata *);
		size_t aligned_size = align_value(needed_size, PAGE_SIZE);
		munmap(mmap_ptr, aligned_size);
	}

}

/**
 * @brief Displays detailed state of allocated memory with hexdumps
 * Shows memory contents, fragmentation, and statistics
 */
void show_alloc_mem_ex() {

	pthread_mutex_lock(&g_tracker.alloc_lock);

	size_t total = 0;
	size_t fragmentation = 0;
	size_t tiny_zones = 0;
	size_t small_zones = 0;
	size_t large_blocks = 0;

	ft_putstr_fd("\n========== EXTENDED MEMORY ALLOCATION MAP ==========\n\n", 1);

	t_zone_metadata *zone = g_tracker.tiny_chunk;

	while (zone) {
		tiny_zones++;
		zone = zone->next;
	}
	
	zone = g_tracker.small_chunk;

	while (zone) {
		small_zones++;
		zone = zone->next;
	}
	
	t_block_metadata *block = g_tracker.used_large_chunk;

	while (block) {
		large_blocks++;
		block = block->next;
	}

	ft_putstr_fd("Zone Summary:\n", 1);

	ft_putstr_fd("TINY zones: ", 1);
	put_unbr_fd(tiny_zones, 1);

	ft_putstr_fd("\nSMALL zones: ", 1);
	put_unbr_fd(small_zones, 1);

	ft_putstr_fd("\nLARGE blocks: ", 1);
	put_unbr_fd(large_blocks, 1);
    
	ft_putstr_fd("\n\n", 1);

	if (g_tracker.tiny_chunk) {
		ft_putstr_fd("========== TINY ALLOCATIONS ==========\n", 1);
		print_zone_ex(g_tracker.tiny_chunk, "TINY", &total, &fragmentation, 1);
		ft_putchar_fd('\n', 1);
	}

	if (g_tracker.small_chunk) {
		ft_putstr_fd("========== SMALL ALLOCATIONS ==========\n", 1);
		print_zone_ex(g_tracker.small_chunk, "SMALL", &total, &fragmentation, 1);
		ft_putchar_fd('\n', 1);
	}

	if (g_tracker.used_large_chunk) {
		ft_putstr_fd("========== LARGE ALLOCATIONS ==========\n", 1);
		print_block_ex(g_tracker.used_large_chunk, &total, 1);
		ft_putchar_fd('\n', 1);
	}

	ft_putstr_fd("========== STATISTICS ==========\n", 1);
	ft_putstr_fd("Total allocated: ", 1);
	put_unbr_fd(total, 1);
	ft_putstr_fd(" bytes\n", 1);
	
	ft_putstr_fd("Fragmentation: ", 1);
	put_unbr_fd(fragmentation, 1);
	ft_putstr_fd(" bytes\n", 1);
	
	if (total > 0) {
		size_t fragmentation_percent = (fragmentation * 100) / (total + fragmentation);
		ft_putstr_fd("Fragmentation ratio: ", 1);
		put_unbr_fd(fragmentation_percent, 1);
		ft_putstr_fd("%\n", 1);
	}
	
	ft_putstr_fd("====================================\n\n", 1);
	pthread_mutex_unlock(&g_tracker.alloc_lock);

}
