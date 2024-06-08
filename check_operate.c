/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 01:12:48 by abadouab          #+#    #+#             */
/*   Updated: 2024/06/08 02:32:34 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*inject_spaces(t_minishell *ms, char *s)
{
	char			*str;
	t_inject_data	data;

	if (!s)
		return (NULL);
	(TRUE) && (data.len = ft_strlen(s), data.len += count_op(s),
		data.i = 0, data.j = 0, data.quotes = -1);
	if (check_par(s))
		return (syntax_err(ms, "syntax error: unexpected end of file\n"
				, 258), NULL);
	str = allocate(&ms->leaks, data.len + 1, sizeof(char));
	if (!str)
		error_handler(ms);
	while (s[data.i])
		copy_and_inject_spaces(&data, s, str);
	str[data.j] = '\0';
	return (str);
}

int	check_ops_and_cmds(t_minishell *ms)
{
	int	i;
	int	cmd;
	int	ops;
	// int	par_exist;

	(1) && (i = 0, cmd = 0, ops = 0);
	while (ms->tokens[i])
	{
		if (check_token_op(ms->tokens[i]))
			ops++;
		else if (ms->tokens[i][0] != '(' && ms->tokens[i][0] != ')')
		{
			cmd++;
			while (ms->tokens[i + 1] && ms->tokens[i + 1][0] != '('
				&& ms->tokens[i + 1][0] != ')'
				&& !check_token_op(ms->tokens[i + 1]))
					i++;
		}
		i++;
	}
	if (ops + 1 != cmd)
		return (syntax_err(ms,
			"syntax error near unexpected token\n", 258), -1);
	return (0);
}
