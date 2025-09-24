/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 02:05:31 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/25 08:54:16 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

size_t	ft_lstsize(t_list *node)
{
	size_t	length;
	t_list	*current;

	length = 0;
	current = node;
	while (current != NULL)
	{
		length++;
		current = current->next;
	}
	return (length);
}
