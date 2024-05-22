/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:27:59 by abadouab          #+#    #+#             */
/*   Updated: 2023/12/07 21:17:10 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

static void	free_split(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	**split_words(char	**str, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	pos;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		pos = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > pos)
		{
			len = i - pos;
			str[j] = malloc((len + 1) * sizeof(char));
			if (!str[j])
				return (NULL);
			ft_strlcpy(str[j++], s + pos, len + 1);
		}
	}
	return (str[j] = NULL, str);
}

char	**ft_split(char const *s, char c)
{
	size_t	len;
	char	**str;

	if (!s)
		return (NULL);
	len = count_words(s, c) + 1;
	str = malloc(len * sizeof(char *));
	if (!str)
		return (NULL);
	if (!split_words(str, s, c))
	{
		free_split(str);
		return (NULL);
	}
	return (str);
}
