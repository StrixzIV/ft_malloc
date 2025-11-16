/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:24:02 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/24 13:10:01 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_strncmp(const char *a, const char *b, size_t n_character)
{
	size_t	idx;

	idx = 0;
	if (n_character == 0)
		return (0);
	while (a[idx] == b[idx] && (a[idx] && b[idx]) && idx < (n_character - 1))
		idx++;
	return ((unsigned char) a[idx] - (unsigned char) b[idx]);
}
