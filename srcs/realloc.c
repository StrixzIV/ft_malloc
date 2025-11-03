/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <strixz.self@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:06:32 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/11/04 02:06:32 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void    *intern_realloc(void *ptr, size_t size) {

	// If ptr is NULL, realloc() behaves like malloc()
	if (ptr == NULL) {
        return intern_malloc(size);
    }

	// If size is 0, realloc() behaves like free()
    if (size == 0) {
        intern_free(ptr);
        return NULL;
    }

    t_block_metadata *metadata = (t_block_metadata *)((char *)(ptr) - aligned_header_size());

    if (metadata->block_size >= size) {
        return ptr;
    }

    void *new_address = intern_malloc(size);
    if (new_address == NULL) {
        return NULL;
    }

    // Copy data from the old block to the new one.
    // Copy the *smaller* of the two buffer sizes.
    size_t min_size = (metadata->block_size < size) ? metadata->block_size : size;
    ft_memcpy(new_address, ptr, min_size);

    intern_free(ptr);

    return new_address;

}

void    *realloc(void *ptr, size_t size) {

    pthread_mutex_lock(&g_tracker.alloc_lock);
    void *new_address = intern_realloc(ptr, size);
    pthread_mutex_unlock(&g_tracker.alloc_lock);
    
	return new_address;

}
