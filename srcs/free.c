/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <strixz.self@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:43:30 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/11/17 01:48:26 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void    intern_free(void *ptr) {
    
    t_block_metadata *metadata = (t_block_metadata *)((char *)(ptr) - aligned_header_size());

    if (g_config.is_debug) {
        ft_putstr_fd(" (", 2);
        put_unbr_fd(metadata->block_size, 2);
        ft_putstr_fd(" bytes)\n", 2);
    }

    if (g_config.is_scribble) {

        ft_memset(ptr, 0x55, metadata->block_size);

        if (g_config.is_debug) {
            ft_putstr_fd("- [Scribbled with 0x55]\n", 2);
        }

    }

    // A block is TINY or SMALL if it belongs to a zone.
    // A block is LARGE if it was a standalone mmap() call and has no zone.
    if (metadata->zone != NULL) {
        free_block(metadata);
    }
    
    // LARGE block
    else {
        remove_block(&g_tracker.used_large_chunk, metadata);
        size_t total_size = metadata->block_size + aligned_header_size();
        munmap(metadata, total_size);
    }
    
}

void    free(void *ptr) {

    if (ptr == NULL) {

        if (g_config.is_debug) {
            ft_putstr_fd("[FREE] NULL pointer, ignoring\n", 2);
        }

        return;

    }

    if (g_config.is_debug) {
        ft_putstr_fd("[FREE] Freeing 0x", 2);
        put_hex_fd((size_t) ptr, 2);
    }

    pthread_mutex_lock(&g_tracker.alloc_lock);
    int valid = is_valid_pointer(ptr);
    pthread_mutex_unlock(&g_tracker.alloc_lock);

    if (!valid) {

        if (g_config.is_check) {
            ft_putstr_fd("\n[FREE ERROR] Invalid pointer: 0x", 2);
            put_hex_fd((size_t)ptr, 2);
            ft_putstr_fd(" - not allocated by malloc!\n", 2);
            return;
        }

        if (g_config.is_debug) {
            ft_putstr_fd(" [Valid]", 2);
        }
        
        return;

    }

    pthread_mutex_lock(&g_tracker.alloc_lock);
    intern_free(ptr);
    pthread_mutex_unlock(&g_tracker.alloc_lock);

}
