/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:22:24 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/24 13:10:01 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

size_t	ft_strlcat(char *destination, const char *source, size_t n)
{
	size_t		dst_len;
	size_t		total_len;
	const char	*string;

	if ((!destination || !source) && !n)
		return (0);
	string = source;
	dst_len = 0;
	while (*(destination + dst_len) && dst_len < n)
		dst_len++;
	if (dst_len < n)
		total_len = dst_len + ft_strlen(string);
	else
		return (n + ft_strlen(string));
	while (*string && (dst_len + 1) < n)
	{
		*(destination + dst_len) = *string++;
		dst_len++;
	}
	*(destination + dst_len) = '\0';
	return (total_len);
}
