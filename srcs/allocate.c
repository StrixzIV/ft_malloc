/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <strixz.self@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:24:54 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/11/16 23:56:26 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

/**
 * @brief Allocates raw memory from the OS using mmap.
 */
void    *allocate(void *address, size_t size) {
    return mmap(address, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

/**
 * @brief Creates a new memory zone (TINY or SMALL) and adds it to the list.
 *
 * @param lst_head A pointer to the head of the zone list (e.g., g_tracker.tiny_chunk).
 * @param block_size The size of the blocks this zone will manage (e.g., TINY_BLOCK_SIZE).
 * @return A pointer to the newly created zone, or NULL on failure.
 */
void    *create_alloc_zone(t_zone_metadata **lst_head, size_t block_size) {

    assert(sizeof(t_zone_metadata) < block_size  && "t_zone_metadata must be smaller than the block size");

    size_t zone_size = align_value(block_size * MIN_BLOCK_COUNT_IN_ZONE, PAGE_SIZE);
    t_zone_metadata *zone = (t_zone_metadata *) allocate(NULL, zone_size);

    if (zone == MAP_FAILED) {
        return NULL;
    }

    zone->allocated_size = zone_size;
    add_zone(lst_head, zone);

    zone->used_blocks = NULL;
    zone->freed_blocks = (t_block_metadata *) align_value((size_t)(zone + 1), MIN_ALIGNMENT);

    // Calculate the address of the user buffer for this first block
    void *buffer_addr = (void *)((char *)(zone->freed_blocks) + aligned_header_size());

    // The first free block's buffer spans the entire rest of the zone
    zone->freed_blocks->block_size = ((char *) zone) + zone_size - ((char *) buffer_addr);
    zone->freed_blocks->prev = NULL;
    zone->freed_blocks->next = NULL;
    zone->freed_blocks->zone = zone;

    return zone;

}

/**
 * @brief Finds a free block in a zone list, allocates it, and optionally splits it.
 *
 * @param zone The first zone in the list to search (e.g., g_tracker.tiny_chunk).
 * @param size The requested *user buffer* size.
 * @return A pointer to the user buffer of the allocated block, or NULL if no block is found.
 */
void    *allocate_block(t_zone_metadata *zone, size_t size) {

    size_t header_size = aligned_header_size();

    while (zone) {
        t_block_metadata *free_block = zone->freed_blocks;

        while (free_block) {
            
            if (free_block->block_size >= size) {
                
                t_block_metadata *alloc_block = free_block;

                // Check if we can split the block.
                // We need enough space for the requested size, a new header, and a minimum-sized fragment.
                if (free_block->block_size > size + header_size + MIN_FRAGMENTATION_SIZE) {
                    
                    // Calculate the header address for the new free block
                    t_block_metadata *new_free_block = (t_block_metadata *) align_value(
                        (size_t)((char *)alloc_block + header_size + size), MIN_ALIGNMENT
                    );

                    *new_free_block = *alloc_block;

                    void *original_buffer_start = (void *)((char *)alloc_block + header_size);
                    void *original_buffer_end = (void *)((char *)original_buffer_start + new_free_block->block_size);

                    void *new_free_buffer_start = (void *)((char *)new_free_block + header_size);
                    new_free_block->block_size = (size_t)((char *)original_buffer_end - (char *)new_free_buffer_start);

                    alloc_block->block_size = (size_t)((char *)new_free_block - (char *)original_buffer_start);

                    if (new_free_block->prev) {
                        new_free_block->prev->next = new_free_block;
                    }
                    
                    else {
                        zone->freed_blocks = new_free_block;
                    }
                    
                    if (new_free_block->next) {
                        new_free_block->next->prev = new_free_block;
                    }

                }
                
                else {
                    remove_block(&zone->freed_blocks, alloc_block);
                }
                
                add_block(&zone->used_blocks, alloc_block);
                return (void *)((char *)alloc_block + header_size);
            
            }

            free_block = free_block->next;
        
        }

        zone = zone->next;
    
    }

    return NULL;

}

/**
 * @brief Frees a block within a TINY or SMALL zone.
 *
 * This function handles removing the block from the used list,
 * adding it to the free list in address-sorted order,
 * and coalescing (merging) with adjacent free blocks.
 *
 * @param block The header of the block to be freed.
 */
void    free_block(t_block_metadata *block) {
    
    t_zone_metadata *zone = block->zone;
    
    if (!zone)
        return ;

    remove_block(&zone->used_blocks, block);

    t_block_metadata *free_list = zone->freed_blocks;
    size_t header_size = aligned_header_size();

    // Case 1: The free list is empty
    // This block becomes the new (and only) free block
    if (free_list == NULL) {
        block->prev = NULL;
        block->next = NULL;
        zone->freed_blocks = block;
    }

    // Case 2: The block to be freed is *before* the first free block (address-wise)
    else if (free_list > block) {

        t_block_metadata *next = free_list;
        
        // Coalesce (merge) with the *next* block if adjacent
        // Check if end of 'block' buffer == start of 'next' header
        if (next && (char *) block + header_size + block->block_size == (char *) next) {
            block->block_size += header_size + next->block_size;
            next = next->next;
        }

        block->prev = NULL;
        zone->freed_blocks = block;

        block->next = next;
        
        if (block->next) {
            block->next->prev = block;
        }

    }

    // Case 3: The block to be freed is *after* some other free block
    else {
        
        t_block_metadata *current = free_list;
        
        while (current->next && current->next < block) {
            current = current->next;
        }

        t_block_metadata *prev = current;
        t_block_metadata *next = current->next;
        
        // Coalesce with *previous* block if adjacent
        // Check if end of 'prev' buffer == start of 'block' header
        if (prev && (char *)prev + header_size + prev->block_size == (char *)block) {
            prev->block_size += header_size + block->block_size;
            block = prev; 
            prev = prev->prev;
        }

        // Coalesce with *next* block if adjacent
        // Check if end of 'block' buffer == start of 'next' header
        if (next && (char *)block + header_size + block->block_size == (char *)next) {
            block->block_size += header_size + next->block_size;
            next = next->next;
        }

        block->prev = prev;
        
        if (block->prev) {
            block->prev->next = block;
        }

        block->next = next;

        if (block->next) {
            block->next->prev = block;
        }

    }
}
