/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 02:16:20 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/25 08:53:43 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_lstclear(t_list **list, void (*del_func)(void*))
{
	t_list	*current_node;
	t_list	*next_node;

	if (!list || !del_func)
		return ;
	current_node = *list;
	while (current_node != NULL)
	{
		next_node = current_node->next;
		ft_lstdelone(current_node, del_func);
		current_node = next_node;
	}
	*list = NULL;
}
