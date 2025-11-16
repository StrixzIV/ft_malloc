/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:05:27 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/30 08:53:43 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memchr(const void *bytes, int character, size_t n)
{
	size_t		idx;
	const char	*string;

	idx = 0;
	string = (const char *) bytes;
	character = (char) character;
	while (idx < n)
	{
		if (string[idx] == character)
			return ((void *)(string + idx));
		idx++;
	}
	return (NULL);
}
