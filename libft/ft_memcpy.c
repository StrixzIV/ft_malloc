/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:16:07 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/24 13:10:01 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

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
