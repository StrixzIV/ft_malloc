/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:27:56 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/24 13:10:01 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

size_t	ft_strlcpy(char *destination, const char *source, size_t size)
{
	size_t	idx;

	idx = 0;
	if (size == 0)
		return (ft_strlen(source));
	while (source[idx] != '\0' && idx < (size - 1))
	{
		destination[idx] = source[idx];
		idx++;
	}
	destination[idx] = '\0';
	return (ft_strlen(source));
}
