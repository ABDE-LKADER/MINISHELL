/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:41:56 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/02 09:41:57 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *s, int *j, char *quotes)
{
	if (*quotes != -1 && *quotes == *(s + *j))
	{
		*quotes = -1;
		(*j)++;
		return (1);
	}
	else if (*quotes == -1 && (*(s + *j) == '\"' || *(s + *j) == '\''))
	{
		*quotes = *(s + *j);
		(*j)++;
		return (1);
	}
	return (0);
}

int	check_parentheses(char *s, int *j)
{
	int	level;

	level = 0;
	if (s && *(s + *j) == '(')
	{
		level++;
		(*j)++;
		while (s && *(s + *j))
		{
			if (s && *(s + *j) == '(')
				level++;
			if (s && *(s + *j) == ')')
				level--;
			(*j)++;
			if (level == 0)
				break ;
		}
		return (1);
	}
	return (0);
}

int	check_operators(char *s, int *j)
{
	if (s && *(s + *j) && *(s + *j + 1) && cmp_operators(*(s + *j))
		&& cmp_operators(*(s + *j + 1)))
	{
		(*j) += 2;
		return (1);
	}
	if (cmp_operators(*(s + *j)) || (*(s + *j) && cmp_operators(*(s + *j + 1))))
	{
		(*j)++;
		return (1);
	}
	return (0);
}

void	tokenize_operators(char *s, int *j, char **arr, int w)
{
	if (*(s + *j) && cmp_operators(*(s + *j)))
		(*j)--;
	else if (arr[w][0] && cmp_operators(arr[w][0]))
		(*j)--;
}

void	get_tokens(char *s, int *j, char *quotes)
{
	*j = 0;
	while ((*(s + *j) && !check_sep(*(s + *j))) || (*(s + *j) && *quotes != -1))
	{
		if (check_quotes(s, j, quotes))
			;
		else
			(*j)++;
	}
}
