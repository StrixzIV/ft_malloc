/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:18:24 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/25 09:17:38 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *) ft_calloc(size + 1, sizeof(char));
	if (!str)
		return (NULL);
	return (str);
}

static int	get_digit_length(int nbr)
{
	int	len;

	len = 0;
	if (nbr < 1)
		len++;
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static int	ft_abs(int number)
{
	if (number < 0)
		return (-number);
	return (number);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	int				sign;
	int				len;
	char			*result;

	sign = 1;
	if (n < 0)
		sign = -1;
	len = get_digit_length(n);
	result = ft_strnew(len);
	if (!result)
		return (NULL);
	result[len] = '\0';
	nbr = ft_abs(n);
	while (len--)
	{
		result[len] = '0' + (nbr % 10);
		nbr /= 10;
	}
	if (sign == -1)
		result[0] = '-';
	return (result);
}
