/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 07:27:14 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/25 09:17:56 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *) ft_calloc(size + 1, sizeof(char));
	if (!str)
		return (NULL);
	return (str);
}

static char	*ft_strcpy(char *destination, const char *source)
{
	int	idx;

	idx = 0;
	while (source[idx] != '\0')
	{
		destination[idx] = source[idx];
		idx++;
	}
	destination[idx] = '\0';
	return (destination);
}

char	*ft_strdup(const char *source)
{
	char	*dupliclate;

	dupliclate = ft_strnew(ft_strlen(source));
	if (dupliclate != NULL)
		ft_strcpy(dupliclate, source);
	return (dupliclate);
}
