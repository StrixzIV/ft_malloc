/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 02:16:20 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/30 08:46:27 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_lstadd_back(t_list **list, t_list *node)
{
	if (!(*list) || !node)
	{
		*list = node;
		return ;
	}
	while (*list != NULL)
		list = &(*list)->next;
	*list = node;
}
