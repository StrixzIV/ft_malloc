/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:52:53 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/25 08:53:47 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

t_list	*ft_lstlast(t_list *node)
{
	t_list	*current_node;

	if (!node)
		return (NULL);
	current_node = node;
	while (current_node->next != NULL)
		current_node = current_node->next;
	return (current_node);
}
