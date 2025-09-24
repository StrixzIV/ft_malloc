/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:52:53 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/25 12:14:19 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

t_list	*ft_lstmap(t_list *list, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;

	if (!list || !f || !del)
		return (0);
	new_list = ft_lstnew(f(list->content));
	if (!new_list)
		return (0);
	new_node = new_list;
	list = list->next;
	while (list)
	{
		new_node->next = ft_lstnew(f(list->content));
		if (!new_node->next)
		{
			ft_lstclear(&new_list, del);
			return (0);
		}
		new_node = new_node->next;
		list = list->next;
	}
	return (new_list);
}
