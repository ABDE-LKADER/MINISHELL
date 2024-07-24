/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:44:38 by abbaraka          #+#    #+#             */
/*   Updated: 2024/07/24 14:23:32 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_sep(char c)
{
	char	sp[7];
	int		i;

	sp[0] = ' ';
	sp[1] = '\t';
	sp[2] = '\n';
	sp[3] = '\r';
	sp[4] = '\f';
	sp[5] = '\v';
	sp[6] = '\0';
	i = 0;
	while (sp[i])
	{
		if (c == sp[i])
			return (1);
		i++;
	}
	return (0);
}

int	cmp_operators(char c)
{
	char	operators[5];
	int		i;

	operators[0] = '|';
	operators[1] = '<';
	operators[2] = '>';
	operators[3] = '&';
	operators[4] = '\0';
	i = 0;
	while (operators[i] != '\0')
	{
		if (operators[i] == c)
			return (operators[i]);
		i++;
	}
	return (0);
}

static char	**fill_in(t_allocate **leaks, char **arr, char *s)
{
	int		j;
	int		i;
	int		w;
	char	quotes;
	int		len;

	(1) && (w = 0, quotes = -1, len = words_counter(s));
	while (*s)
	{
		while (*s && check_sep(*s))
			s++;
		get_tokens(s, &j, &quotes);
		arr[w] = allocate(leaks, j + 1, sizeof(char));
		if (!arr[w])
			return (NULL);
		(ft_strlcpy(arr[w], s, j + 1), tokenize_operators(s, &j, arr, w));
		i = 0;
		while (*s && i <= j)
			(1) && (s++, i++);
		if (w < len)
			w++;
	}
	arr[w] = NULL;
	return (arr);
}

char	**ft_split_op(t_allocate **leaks, char const *s)
{
	char	**arr;
	int		count;

	if (!s)
		return (NULL);
	count = words_counter(s);
	arr = allocate(leaks, count + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	return (fill_in(leaks, arr, (char *)s));
}
