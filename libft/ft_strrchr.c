/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:05:27 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/30 08:54:55 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strrchr(const char *string, int character)
{
	int		idx;
	char	*result;

	idx = 0;
	result = NULL;
	character = (char) character;
	while (string[idx] != '\0')
	{
		if (string[idx] == character)
			result = (char *)(string + idx);
		idx++;
	}
	if (string[idx] == character)
		result = (char *)(string + idx);
	return (result);
}
