/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:52:53 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/25 08:53:44 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_lstiter(t_list *node, void (*function)(void *))
{
	t_list	*current_node;

	if (!node || !function)
		return ;
	current_node = node;
	while (current_node != NULL)
	{
		function(current_node->content);
		current_node = current_node->next;
	}
}
