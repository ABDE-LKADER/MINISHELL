/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:43:00 by abbaraka          #+#    #+#             */
/*   Updated: 2024/07/27 18:22:46 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	sep_check(char sep, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (charset[i] == sep)
			return (1);
		i++;
	}
	if (sep == '\0')
		return (1);
	return (0);
}

static void	set_word(char *dest, char *src, char *charset)
{
	int	i;

	i = 0;
	while (sep_check(src[i], charset) == 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static void	split_str(t_allocate **leaks, char **dest, char *str, char *charset)
{
	int	i;
	int	j;
	int	w;

	i = 0;
	w = 0;
	while (str[i] != '\0')
	{
		if (sep_check(str[i], charset) == 1)
			i++;
		else
		{
			j = 0;
			while (sep_check(str[i + j], charset) == 0)
				j++;
			dest[w] = allocate(leaks, sizeof(char *), j + 1);
			if (!dest[w])
				return ;
			set_word(dest[w], str + i, charset);
			i += j;
			w++;
		}
	}
}

static int	counter_words(char *str, char *charset)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (sep_check(str[i], charset) == 0
			&& sep_check(str[i + 1], charset) == 1)
			counter++;
		i++;
	}
	return (counter);
}

char	**split_args(t_allocate **leaks, char *str, char *charset)
{
	int		num;
	char	**dest;

	num = counter_words(str, charset);
	dest = allocate(leaks, sizeof(char *), num + 1);
	if (!dest)
		return (NULL);
	split_str(leaks, dest, str, charset);
	dest[num] = 0;
	return (dest);
}
