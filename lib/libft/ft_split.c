/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 11:11:10 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/25 11:54:22 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static char	**deallocate(char **string_array, int length)
{
	while (length > 0)
	{
		length--;
		free(string_array[length]);
	}
	free(string_array);
	return (NULL);
}

static size_t	count_elements(const char *string, char delimiter)
{
	size_t	idx;
	size_t	count;

	idx = 0;
	count = 0;
	while (string[idx] != '\0')
	{
		if (string[idx] == delimiter)
		{
			idx++;
			continue ;
		}
		count++;
		while (string[idx] != '\0' && string[idx] != delimiter)
			idx++;
	}
	return (count);
}

static char	*read_word(char *result, const char *s, size_t i, size_t l)
{
	size_t	j;

	j = 0;
	while (l > 0)
	{
		result[j] = s[i - l];
		j++;
		l--;
	}
	result[j] = '\0';
	return (result);
}

char	**split_words(char const *s, char d, char **res, size_t n)
{
	size_t	idx;
	size_t	n_word;
	size_t	word_length;

	idx = 0;
	n_word = 0;
	word_length = 0;
	while (n_word < n)
	{
		while (s[idx] != '\0' && s[idx] == d)
			idx++;
		while (s[idx] != '\0' && s[idx] != d)
		{
			word_length++;
			idx++;
		}
		res[n_word] = (char *) ft_calloc(word_length + 1, sizeof(char));
		if (!res)
			return (deallocate(res, n_word));
		read_word(res[n_word], s, idx, word_length);
		word_length = 0;
		n_word++;
	}
	res[n_word] = 0;
	return (res);
}

char	**ft_split(char const *string, char delimiter)
{
	char			**results;
	size_t			n_results;

	if (!string)
		return (NULL);
	n_results = count_elements(string, delimiter);
	results = (char **) ft_calloc(n_results + 1, sizeof(char *));
	if (!results)
		return (NULL);
	results = split_words(string, delimiter, results, n_results);
	return (results);
}
