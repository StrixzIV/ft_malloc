/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <strixz.self@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:16:07 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/11/04 02:03:59 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	void	*dest_ptr;

	dest_ptr = destination;
	if (!destination && !source)
		return (destination);
	while (n--)
		*((unsigned char *) destination++) = *((unsigned char *) source++);
	return (dest_ptr);
}
