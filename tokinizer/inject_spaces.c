/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inject_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:44:42 by abbaraka          #+#    #+#             */
/*   Updated: 2024/07/25 09:11:00 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_spaces(char quotes, char *s, int i, int *space_counter)
{
	if (quotes == -1 && (s[i] == '(' || s[i] == ')')
		&& (s[i + 1] || !check_sep(s[i + 1])))
		(*space_counter)++;
	if (quotes == -1 && (s[i] || !check_sep(s[i]))
		&& (s[i + 1] == '(' || s[i + 1] == ')'))
		(*space_counter)++;
	else if (quotes == -1 && (s[i] && !check_sep(s[i])
			&& !cmp_operators(s[i])) && (cmp_operators(s[i + 1])))
		(*space_counter)++;
	else if (quotes == -1 && (cmp_operators(s[i]) && (s[i + 1]
				&& !check_sep(s[i + 1]) && cmp_operators(s[i + 1])
				&& s[i] != s[i + 1])))
		(*space_counter)++;
	else if (quotes == -1 && (cmp_operators(s[i]) && (s[i + 1]
				&& !check_sep(s[i + 1]) && !cmp_operators(s[i + 1]))))
		(*space_counter)++;
	else if (quotes == -1 && cmp_operators(s[i])
		&& (!check_sep(s[i + 1]) && !cmp_operators(s[i + 1])))
		(*space_counter)++;
	return (*space_counter);
}

int	count_op(char *s)
{
	int		i;
	int		space_counter;
	char	quotes;

	(1) && (i = 0, space_counter = 0, quotes = -1);
	while (s[i])
	{
		if (s[i] && quotes == -1 && (s[i] == '\"' || s[i] == '\''))
		{
			quotes = s[i];
			while (s[i] && s[i] != quotes)
				i++;
		}
		else if (s[i] && s[i] == quotes)
		{
			if (cmp_operators(s[i + 1]) || s[i + 1] == '(' || s[i + 1] == ')')
				space_counter++;
			(1) && (quotes = -1, i++);
		}
		if (s[i] == '\0')
			break ;
		count_spaces(quotes, s, i, &space_counter);
		i++;
	}
	return (space_counter);
}

int	copy_quotes(t_inject_data *data, char *s, char *str)
{
	if (!s || s[data->i] == '\0')
		return (1);
	if (s[data->i] && data->quotes == -1
		&& (s[data->i] == '\"' || s[data->i] == '\''))
	{
		data->quotes = s[data->i];
		while (s[data->i] && s[data->i] != data->quotes)
			(1) && (str[data->j] = s[data->i], data->i++, data->j++);
	}
	else if (s[data->i] && s[data->i] == data->quotes)
	{
		(1) && (data->quotes = -1, str[data->j] = s[data->i],
		data->i++, data->j++);
		if (data->quotes == -1 && (s[data->i - 1] == '\''
				|| s[data->i - 1] == '\"') && (s[data->i] == '('
				|| s[data->i] == ')'))
			(1) && (str[data->j] = ' ', data->j++, str[data->j] = s[data->i],
			data->i++, data->j++);
	}
	return (0);
}

int	inject_spaces_between_par(t_inject_data *data, char *s, char *str)
{
	if (data->quotes == -1 && (s[data->i] && !check_sep(s[data->i]))
		&& (s[data->i + 1] == '(' || s[data->i + 1] == ')'))
		return (str[data->j] = s[data->i], data->j++,
			str[data->j] = ' ', data->j++, data->i++, 1);
	else if (data->quotes == -1 && (s[data->i] == '(' || s[data->i] == ')')
		&& (s[data->i + 1] && !check_sep(s[data->i + 1])))
		return (str[data->j] = s[data->i], data->j++,
			str[data->j] = ' ', data->j++, data->i++, 1);
	return (0);
}

void	copy_and_inject_spaces(t_inject_data *data, char *s, char *str)
{
	if (copy_quotes(data, s, str))
		return ;
	if (data->quotes == -1 && data->i != 0
		&& cmp_operators(s[data->i]) && s[data->i - 1]
		&& (!check_sep(s[data->i - 1]) && !cmp_operators(s[data->i - 1])))
	{
		(1) && (str[data->j] = ' ', data->j++,
			str[data->j] = s[data->i], data->j++);
		if (cmp_operators(s[data->i]) && s[data->i + 1]
			&& (!check_sep(s[data->i + 1]) && (!cmp_operators(s[data->i + 1])
					|| (cmp_operators(s[data->i + 1])
						&& s[data->i] != s[data->i + 1]))))
			(1) && (str[data->j] = ' ', data->j++);
		data->i++;
	}
	else if (data->quotes == -1 && cmp_operators(s[data->i]) && s[data->i + 1]
		&& (!check_sep(s[data->i + 1]) && (!cmp_operators(s[data->i + 1])
				|| (cmp_operators(s[data->i + 1])
					&& s[data->i] != s[data->i + 1]))))
		(1) && (str[data->j] = s[data->i], data->j++,
		str[data->j] = ' ', data->j++, data->i++);
	else if (inject_spaces_between_par(data, s, str))
		;
	else if (s[data->i])
		(1) && (str[data->j] = s[data->i], data->j++, data->i++);
}
