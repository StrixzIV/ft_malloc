/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <strixz.self@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 03:18:25 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/09/25 03:18:25 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>
# include <pthread.h>
# include <sys/mman.h>

// Mandatory functions

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

void	show_alloc_mem();

#endif
