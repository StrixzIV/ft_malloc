/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <strixz.self@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:43:30 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/11/04 02:57:47 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void    intern_free(void *ptr) {
    
    t_block_metadata *metadata = (t_block_metadata *)((char *)(ptr) - aligned_header_size());

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

    if (ptr == NULL)
        return;

    pthread_mutex_lock(&g_tracker.alloc_lock);
    intern_free(ptr);
    pthread_mutex_unlock(&g_tracker.alloc_lock);

}
