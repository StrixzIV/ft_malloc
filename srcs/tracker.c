/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <strixz.self@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 10:11:40 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/11/04 02:45:23 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_malloc_tracker g_tracker = {
    .alloc_lock = PTHREAD_MUTEX_INITIALIZER,
    .tiny_chunk = NULL,
    .small_chunk = NULL,
    .free_large_chunk = NULL,
    .used_large_chunk = NULL
};

void    add_block(t_block_metadata **lst_head, t_block_metadata *header) {
    header->prev = NULL;
    header->next = *lst_head;
    if (*lst_head != NULL)
        (*lst_head)->prev = header;
    *lst_head = header;
}

void    add_zone(t_zone_metadata **lst_head, t_zone_metadata *header) {
    header->prev = NULL;
    header->next = *lst_head;
    if (*lst_head != NULL)
        (*lst_head)->prev = header;
    *lst_head = header;
}

void    remove_block(t_block_metadata **lst_head, t_block_metadata *header) {
    if (*lst_head == header)
        *lst_head = header->next;
    if (header->prev)
        header->prev->next = header->next;
    if (header->next)
        header->next->prev = header->prev;
    header->prev = NULL;
    header->next = NULL;
}

void    remove_zone(t_zone_metadata **lst_head, t_zone_metadata *header) {
    if (*lst_head == header)
        *lst_head = header->next;
    if (header->prev)
        header->prev->next = header->next;
    if (header->next)
        header->next->prev = header->prev;
    header->prev = NULL;
    header->next = NULL;
}
