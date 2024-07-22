/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:18:54 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/22 13:27:00 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	only_var(t_minishell *ms, char *arg)
{
	char	*hold;

	if (*arg != '$')
		return (TRUE);
	arg++;
	hold = arg;
	while (*arg)
	{
		if (!ft_isalnum(*arg) && *arg != '_' && *arg != '$')
			return (TRUE);
		arg++;
	}
	if (get_env_val(ms, hold))
		return (TRUE);
	return (FALSE);
}

int	check_redirection_symbole(t_minishell *ms, int *i, int *redir_set)
{
	if (!ft_strncmp(ms->tokens[*i], ">", ft_strlen(ms->tokens[*i]))
		|| !ft_strncmp(ms->tokens[*i], "<", ft_strlen(ms->tokens[*i]))
		|| !ft_strncmp(ms->tokens[*i], ">>", ft_strlen(ms->tokens[*i]))
		|| !ft_strncmp(ms->tokens[*i], "<<", ft_strlen(ms->tokens[*i])))
	{
		if (!ms->tokens[*i + 1])
			return (1);
		set_redir(ms, i);
		if (check_if_operator(ms->tokens[*i + 1])
			|| check_token_op(ms->tokens[*i + 1]))
			return (1);
		ms->tree->redir[ms->tree->redir_index].ambig_var = ms->tokens[*i + 1];
		ms->tree->redir[ms->tree->redir_index].redir_name = splite_mult_args
			(ms, ms->tokens[*i + 1], TRUE, TRUE);
		if (ft_strchr(ms->tokens[*i + 1], '$') && !ft_strchr(ms->tokens[*i + 1],
			'\'') && !ft_strchr(ms->tokens[*i + 1], '\"') && ft_strchr(ms->tree
			->redir[ms->tree->redir_index].redir_name, ' '))
			ms->tree->redir[ms->tree->redir_index].ambiguous = 1;
		ms->tree->redir_index++;
		*redir_set = 1;
		if (redir_set)
			(*i) += 2;
	}
	return (0);
}

int	check_redirection(t_minishell *ms, int *i, int *redir_set)
{
	if (check_redirection_symbole(ms, i, redir_set))
		return (syntax_err(ms, NULL,
				"syntax error near unexpected token `newline'", 258),
			ms->tree->syntax_err = 1, 1);
	if (ms->tokens[*i] && check_token_if_redir(ms->tokens[*i]))
		return (syntax_err(ms, NULL, "syntax error", 258), 1);
	*redir_set = 0;
	if (!ms->tree->syntax_err && ms->tokens[*i]
		&& check_if_operator(ms->tokens[*i]))
	{
		if (ms->tokens[*i + 1] && !check_token_op(ms->tokens[*i + 1]))
			check_redirection(ms, i, redir_set);
		else if (!ms->tokens[*i + 1])
			return (syntax_err(ms, NULL,
					"syntax error near unexpected token `newline'", 258),
				ms->tree->syntax_err = 1, 1);
	}
	return (0);
}

int	check_redir_at_end(t_minishell *ms, int *i, int *redir_set)
{
	while (ms->tokens[*i] && !check_token_op(ms->tokens[*i]))
	{
		if (ms->tokens[*i] && check_if_operator(ms->tokens[*i]))
		{
			if (ms->tokens[*i]
				&& check_redirection(ms, i, redir_set))
				return (1);
		}
		if (ms->tokens[*i] && check_valid_op(ms->tokens[*i]))
			return (syntax_err(ms, NULL, "syntax error", 258),
				ms->tree->syntax_err = 1, 1);
		if (!ms->tokens[*i] || check_token_op(ms->tokens[*i]))
			return (0);
		else
			(*i)++;
	}
	return (0);
}
