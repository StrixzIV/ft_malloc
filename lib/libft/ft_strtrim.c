/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 09:41:21 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/25 09:55:56 by jikaewsi         ###   ########.fr       */
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

static int	contains(const char c, const char *charset)
{
	size_t	idx;

	idx = 0;
	while (charset[idx] != '\0')
	{
		if (charset[idx] == c)
			return (1);
		idx++;
	}
	return (0);
}

char	*ft_strtrim(const char *string, const char *charset)
{
	size_t	size;
	char	*result;

	if (!string || !charset)
		return (NULL);
	while (string)
	{
		if (contains((char) *string, charset))
			string++;
		else
			break ;
	}
	size = ft_strlen(string);
	while (size != 0)
	{
		if (contains(string[size - 1], charset))
			size--;
		else
			break ;
	}
	result = ft_strnew(size);
	if (!result)
		return (NULL);
	ft_strlcpy(result, (char *) string, size + 1);
	return (result);
}
