/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:24:02 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/24 13:10:01 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_memcmp(const void *a, const void *b, size_t n)
{
	size_t				idx;
	const unsigned char	*ptr_a;
	const unsigned char	*ptr_b;

	idx = 0;
	ptr_a = (const unsigned char *) a;
	ptr_b = (const unsigned char *) b;
	while (idx < n)
	{
		if (ptr_a[idx] != ptr_b[idx])
			return (ptr_a[idx] - ptr_b[idx]);
		idx++;
	}
	return (0);
}
