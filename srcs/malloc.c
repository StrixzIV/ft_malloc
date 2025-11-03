/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <strixz.self@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 01:58:49 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/11/04 01:58:49 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void    *intern_malloc(size_t size) {

	// Handle TINY allocations
	if (size <= TINY_ALLOC_SIZE) {

        void *address = allocate_block(g_tracker.tiny_chunk, size);
        
		if (address == NULL) {
			
            t_zone_metadata *new_zone = create_alloc_zone(&g_tracker.tiny_chunk, TINY_BLOCK_SIZE);
            
			if (new_zone == NULL) {
				return NULL;
            }

            address = allocate_block(new_zone, size);

        }

        return address;
   
	}

    // Handle SMALL allocations
    else if (size <= SMALL_ALLOC_SIZE) {

        void *address = allocate_block(g_tracker.small_chunk, size);
        
		if (address == NULL) {
			
            t_zone_metadata *new_zone = create_alloc_zone(&g_tracker.small_chunk, SMALL_BLOCK_SIZE);
            
			if (new_zone == NULL) {
                return NULL;
            }
			
            address = allocate_block(new_zone, size);

        }

        return address;
    
	}

    // Handle LARGE allocations
    t_block_metadata *free_large_block = g_tracker.free_large_chunk;

    while (free_large_block && free_large_block->block_size < size) {
        free_large_block = free_large_block->next;
    }

    if (free_large_block) {
        remove_block(&g_tracker.free_large_chunk, free_large_block);
        add_block(&g_tracker.used_large_chunk, free_large_block);
        return (void *)((char *)free_large_block + aligned_header_size());
    }

    const size_t aligned_size = get_aligned_large_block_size(size);
    void *address = allocate(NULL, aligned_size);
    
	if (address == MAP_FAILED) {
        return NULL;
    }

    // Set up the header for the new large block
    t_block_metadata *header = (t_block_metadata *)address;
    header->block_size = aligned_size - aligned_header_size();
    header->zone = NULL;
    
    add_block(&g_tracker.used_large_chunk, header);
    
    return (void *)((char *)header + aligned_header_size());

}


void    *malloc(size_t size) {

    if (size == 0) {
        return NULL;
    }

    pthread_mutex_lock(&g_tracker.alloc_lock);
    void *address = intern_malloc(size);
    pthread_mutex_unlock(&g_tracker.alloc_lock);
    
    return address;

}
