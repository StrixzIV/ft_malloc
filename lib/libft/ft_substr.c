/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:10:06 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/30 08:57:21 by jikaewsi         ###   ########.fr       */
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

static char	*ft_strncpy(char *destination, const char *source, size_t n)
{
	size_t	idx;

	idx = 0;
	while ((idx < n) && (source[idx] != '\0'))
	{
		destination[idx] = source[idx];
		idx++;
	}
	while (idx < n)
	{
		destination[idx] = '\0';
		idx++;
	}
	return (destination);
}

char	*ft_substr(const char *string, unsigned int start_idx, size_t length)
{
	char	*result;

	if (!string)
		return (NULL);
	if (start_idx > ft_strlen(string))
		return (ft_strdup(""));
	if (length > ft_strlen(string) - start_idx)
		length = ft_strlen(string) - start_idx;
	string += start_idx;
	result = ft_strnew(length);
	if (!result)
		return (NULL);
	ft_strncpy(result, string, length);
	return (result);
}
