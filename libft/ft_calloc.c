/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:40:39 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/30 08:49:54 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	length;
	void	*mem_bloc;

	length = size * count;
	if (count == 0 || size == 0)
		return (malloc(0));
	else if ((long) count < 0 || (long) size < 0)
		return (NULL);
	mem_bloc = malloc(length);
	if (!mem_bloc)
		return (NULL);
	ft_bzero(mem_bloc, length);
	return (mem_bloc);
}
