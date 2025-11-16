/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:05:27 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/29 09:59:43 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strchr(const char *string, int character)
{
	int	idx;

	idx = 0;
	if (!string)
		return (NULL);
	if (!character)
		return ((char *) string + ft_strlen(string));
	while (string[idx] != '\0')
	{
		if (string[idx] == (char) character)
			return ((char *) string + idx);
		idx++;
	}
	return (NULL);
}
