/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:07:35 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/25 11:07:47 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_striteri(char *string, void (*function)(unsigned int, char*))
{
	unsigned int	idx;

	if (!string || !function)
		return ;
	idx = 0;
	while (string[idx] != '\0')
	{
		(*function)(idx, string + idx);
		idx++;
	}
}
