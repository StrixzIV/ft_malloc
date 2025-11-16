/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:41:53 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/25 09:18:07 by jikaewsi         ###   ########.fr       */
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

char	*ft_strjoin(const char *a, const char *b)
{
	size_t	idx;
	size_t	offset;
	char	*result;

	idx = -1;
	if (!a || !b)
		return (NULL);
	result = ft_strnew(ft_strlen(a) + ft_strlen(b));
	if (!result)
		return (NULL);
	while (++idx < ft_strlen(a))
		result[idx] = a[idx];
	offset = idx;
	idx = -1;
	while (++idx < ft_strlen(b))
		result[idx + offset] = b[idx];
	result[idx + offset] = '\0';
	return (result);
}
