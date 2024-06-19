/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_counter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:39:27 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/03 20:37:17 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotes_counting(char *s, int *i, int *counter, char quotes_type)
{
	(*i)++;
	while (s[*i] && s[*i] != quotes_type)
		(*i)++;
	if (s[*i] == quotes_type)
		(*i)++;
	else if (s[*i] && cmp_operators(s[*i]))
		;
	else
	{
		while (s[*i] && s[*i] != ' ')
			(*i)++;
		if (s[*i])
			(*i)++;
	}
	if (s[*i] || s[*i] == ' ' || s[*i] == '\0' || cmp_operators(s[*i]))
		(*counter)++;
}

int	quotes_counter(char *s, int *i, int *counter)
{
	if (s[*i] == '\'')
	{
		check_quotes_counting(s, i, counter, '\'');
		return (1);
	}
	else if (s[*i] == '\"')
	{
		check_quotes_counting(s, i, counter, '\"');
		return (1);
	}
	return (0);
}

int	words_counter(const char *s)
{
	int	i;
	int	counter;

	(1) && (i = 0, counter = 0);
	while (s[i])
	{
		if (quotes_counter((char *)s, &i, &counter))
			;
		else if ((!check_sep(s[i])) && (check_sep(s[i + 1])
				|| s[i + 1] == '\0'))
			counter++;
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (counter);
}
