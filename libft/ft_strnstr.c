/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:27:57 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/25 10:56:52 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strnstr(const char *string, const char *pattern, size_t length)
{
	size_t	i;
	size_t	j;

	if (!string && !length)
		return (NULL);
	if (pattern[0] == '\0' || string == pattern)
		return ((char *) string);
	i = 0;
	while (string[i] != '\0' && i < length)
	{
		if (string[i] == pattern[0])
		{
			j = 0;
			while (pattern[j] && string[i + j] && i + j < length
				&& string[i + j] == pattern[j])
				j++;
			if (pattern[j] == '\0')
				return ((char *) string + i);
		}
		i++;
	}
	return (0);
}
