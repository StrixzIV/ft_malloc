/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:18:24 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/25 10:48:57 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_putnbr_fd(int number, int fd)
{
	long	num;

	num = number;
	if (num < 0)
	{
		write(fd, "-", 1);
		num = -num;
	}
	if (num >= 10)
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putchar_fd((num % 10) + '0', fd);
	}
	else
		ft_putchar_fd('0' + num, fd);
}
