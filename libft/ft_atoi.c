/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <strixz.self@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 08:12:49 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/06/27 14:37:32 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *string)
{
	int	idx;
	int	sum;
	int	sign;

	idx = 0;
	sum = 0;
	sign = 1;
	while (string[idx] == ' ' || (string[idx] >= 9 && string[idx] <= 13))
		idx++;
	if (string[idx] == '-' || string[idx] == '+')
	{
		if (string[idx] == '-')
			sign = -sign;
		idx++;
	}
	while (string[idx] >= '0' && string[idx] <= '9')
	{
		sum *= 10;
		sum += string[idx] - '0';
		idx++;
	}
	return (sign * sum);
}
