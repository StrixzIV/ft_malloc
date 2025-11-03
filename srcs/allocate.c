/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <strixz.self@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:24:54 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/09/26 09:05:23 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void    *allocate(void *address, size_t size) {
    return mmap(address, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

void    *create_alloc_zone(t_zone_metadata **lst_head, size_t size) {

    assert(sizeof(t_zone_metadata) < size  && "t_zone_metadata must be smaller than the block size");

    size_t zone_size = align_value(size * MIN_BLOCK_COUNT_IN_ZONE, PAGE_SIZE);
    t_zone_metadata *zone = (t_zone_metadata *) allocate(NULL, zone);

}
