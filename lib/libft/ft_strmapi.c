/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:07:35 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/25 10:58:31 by jikaewsi         ###   ########.fr       */
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

char	*ft_strmapi(const char *string, char (*function)(unsigned int, char))
{
	unsigned int	idx;
	unsigned int	length;
	char			*result;

	if (!string || !function)
		return (NULL);
	length = ft_strlen(string);
	result = ft_strnew(length);
	if (!result)
		return (NULL);
	idx = 0;
	while (idx < length)
	{
		result[idx] = (*function)(idx, string[idx]);
		idx++;
	}
	result[idx] = '\0';
	return (result);
}
