/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <strixz.self@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 18:04:58 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/09/26 08:55:54 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

__uint64_t align_value(size_t value, size_t alignment) {

    if (alignment == 0)
        return value;

    return ((value + alignment - 1) & ~(alignment - 1));

}

size_t aligned_header_size(void) {
    return align_value(sizeof(t_block_metadata), MIN_ALIGNMENT);
}

size_t get_aligned_large_block_size(size_t size) {
    size_t header_size = aligned_header_size();
    return align_value(size + header_size, PAGE_SIZE);
}

size_t get_zone_headers_mem_usage(size_t block_size) {
    size_t header_size = aligned_header_size();
    return block_size + header_size * (MIN_BLOCK_COUNT_IN_ZONE - 1);
}
