/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <strixz.self@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:43:30 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/11/04 01:06:36 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

static void    critical_part(void *ptr) {

    t_block_metadata *metadata = (void *)((t_block_metadata *)((unsigned char *)(ptr) - aligned_header_size()));

    if (metadata->block_size <= TINY_BLOCK_SIZE || metadata->block_size <= SMALL_ALLOC_SIZE)
        free_block(metadata);

}

void    free(void *ptr) {

    if (ptr == NULL)
        return;

    pthread_mutex_lock(&g_tracker.alloc_lock);
    critical_part(ptr);
    pthread_mutex_unlock(&g_tracker.alloc_lock);

}
