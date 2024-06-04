/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_checkers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:39:19 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/04 15:38:21 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_op_syntax(char *token)
{
	char	*ops[5];
	int		i;

	ops[0] = ">";
	ops[1] = "<";
	ops[2] = "<<";
	ops[3] = ">>";
	ops[4] = NULL;
	i = 0;
	while (ops[i])
	{
		if (ft_strncmp(token, ops[i], ft_strlen(token)) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_if_operator(char *token)
{
	char	*ops[3];
	int		i;

	ops[0] = ">";
	ops[1] = "<";
	ops[2] = NULL;
	i = 0;
	while (token && ops[i])
	{
		if (ft_strncmp(token, ops[i], ft_strlen(ops[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	check_args(t_tree *node, char **tokens, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("length %d\n", len);
	while (tokens[i] && !check_token_op(tokens[i]))
	{
		if (tokens[i] && tokens[i + 1] && check_if_operator(tokens[i]))
			i += 2;
		if (tokens[i] && (ft_strncmp(tokens[i], "(", ft_strlen(tokens[i])) == 0
				|| ft_strncmp(tokens[i], ")", ft_strlen(tokens[i])) == 0))
			i++;
		else if (tokens[i])
		{
			if (j < len)
			{
				node->args[j] = tokens[i];
				j++;
			}
			i++;
		}
	}
	printf("--------\n");
	node->args[j] = NULL;
	int k = 0;
	while (node->args[k])
		printf("%s\n", node->args[k]), k++;
}


int	check_redirection(t_minishell *ms, int *i, int *redir_set)
{
	if (ft_strncmp(ms->tokens[*i], ">", ft_strlen(ms->tokens[*i])) == 0
		|| ft_strncmp(ms->tokens[*i], "<", ft_strlen(ms->tokens[*i])) == 0
		|| ft_strncmp(ms->tokens[*i], ">>", ft_strlen(ms->tokens[*i])) == 0
		|| ft_strncmp(ms->tokens[*i], "<<", ft_strlen(ms->tokens[*i])) == 0)
	{
		if (!ms->tokens[*i + 1])
			return (syntax_err(ms, "syntax error near unexpected token `newline'", 258),
			ms->tree->syntax_err = 1, 1);
		set_redir(ms, i);
		if (check_if_operator(ms->tokens[*i + 1])
			|| check_token_op(ms->tokens[*i + 1]))
			return (syntax_err(ms ,"syntax error near unexpected token", 258),
				ms->tree->syntax_err = 1, 1);
		ms->tree->redir[ms->tree->redir_index].redir_name = ms->tokens[*i + 1];
		ms->tree->redir_index++;
		*redir_set = 1;
		if (redir_set)
			(*i) += 2;
	}
	if (ms->tokens[*i] && check_token_if_redir(ms->tokens[*i]))
		return (syntax_err(ms, "syntax error", 258), 1);
	*redir_set = 0;
	if (!ms->tree->syntax_err && ms->tokens[*i] && check_if_operator(ms->tokens[*i]))
	{
		if (ms->tokens[*i + 1] && !check_token_op(ms->tokens[*i + 1]))
			check_redirection(ms, i, redir_set);
		else if (!ms->tokens[*i + 1])
			return (syntax_err(ms, "syntax error near unexpected token `newline'", 258),
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
			return (syntax_err(ms, "syntax error", 258),
				ms->tree->syntax_err = 1, 1);
		if (!ms->tokens[*i] || check_token_op(ms->tokens[*i]))
			return (0);
		else
			(*i)++;
	}
	return (0);
}
