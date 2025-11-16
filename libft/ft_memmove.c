/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:16:07 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/24 13:10:01 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memmove(void *destination, const void *source, size_t length)
{
	unsigned char	*source_ptr;
	unsigned char	*dest_ptr;

	source_ptr = (unsigned char *) source;
	dest_ptr = (unsigned char *) destination;
	if (destination == source)
		return (destination);
	if (source_ptr < dest_ptr)
	{
		while (length--)
			dest_ptr[length] = source_ptr[length];
		return (destination);
	}
	while (length--)
		*(dest_ptr++) = *(source_ptr++);
	return (destination);
}
