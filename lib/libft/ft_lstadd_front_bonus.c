/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 02:16:20 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/25 08:53:42 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_lstadd_front(t_list **list, t_list *node)
{
	if (!(*list) || !node)
	{
		*list = node;
		return ;
	}
	node->next = *list;
	*list = node;
}
