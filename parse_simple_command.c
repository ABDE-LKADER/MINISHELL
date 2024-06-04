/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:39:37 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/04 20:26:29 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_op(char *token)
{
	char	ops[3];
	int		i;

	ops[0] = '|';
	ops[1] = '&';
	ops[2] = '\0';
	i = 0;
	while (ops[i])
	{
		if (token[0] == ops[i] && !check_token_op(token))
			return (1);
		i++;
	}
	return (0);
}

void	set_redir(t_minishell *ms, int *i)
{
	t_tree *node;
	char 	**tokens;

	(1) && (node = ms->tree, tokens = ms->tokens);
	if (ft_strncmp(tokens[*i], ">", ft_strlen(tokens[*i])) == 0)
	{
		node->redir[node->redir_index].redirection = OUT_RED_T;
		node->redir[node->redir_index].fd = -1;
	}
	else if (ft_strncmp(tokens[*i], "<", ft_strlen(tokens[*i])) == 0)
	{
		node->redir[node->redir_index].redirection = IN_RED_T;
		node->redir[node->redir_index].fd = -1;
	}
	else if (ft_strncmp(tokens[*i], ">>", ft_strlen(tokens[*i])) == 0)
	{
		node->redir[node->redir_index].redirection = OUT_RED_APPEND_T;
		node->redir[node->redir_index].fd = -1;
	}
	else if (ft_strncmp(tokens[*i], "<<", ft_strlen(tokens[*i])) == 0
			&& g_sig == 0)
	{
		node->redir[node->redir_index].redirection = HERE_DOC_T;
		node->redir[node->redir_index].fd = ft_open_here_doc(ms, tokens[*i + 1]);
	}
}

int	count_redir(char **tokens)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (tokens[i])
	{
		if (check_if_operator(tokens[i]))
			counter++;
		i++;
	}
	return (counter);
}

int	count_args(char **tokens)
{
	int	i;
	int	j;
	int	counter;

	(1) && (i = 0, j = 0, counter = 0);
	while (tokens[i] && !check_token_op(tokens[i]))
		i++;
	while (j < i)
	{
		if (tokens[j] && tokens[j + 1] && check_if_operator(tokens[j]))
			j += 2;
		if (tokens[j] && !check_if_operator(tokens[j]))
		{
			counter++;
			j++;
		}
		else
			j++;
	}
	return (counter);
}

int	check_op_and_allocate(t_minishell *ms, int *i, int *redir_set)
{
	if (check_token_op(ms->tokens[*i]))
		return (syntax_err(ms, "syntax error", 258), 1);
	ms->tree = allocate(&ms->leaks, 1, sizeof(t_tree));
	if (!ms->tree)
		error_handler(ms);
	(1) && (*redir_set = 0, ms->tree->redir_index = 0,
	ms->tree->syntax_err = 0);
	ms->tree->redir = allocate(&ms->leaks, count_redir(ms->tokens) + 1, sizeof(t_redir));
	if (!ms->tree->redir)
		error_handler(ms);
	ms->tree->args = allocate(&ms->leaks, count_args(ms->tokens + *i) + 1, sizeof(char *));
	if (!ms->tree->args)
		error_handler(ms);
	return (0);
}

t_tree	*parse_simple_command(t_minishell *ms, int *i)
{
	int			redir_set;

	if (check_op_and_allocate(ms, i, &redir_set))
		return (NULL);
	ms->tree->dis_error = check_syntax_err(ms);
	if (check_redirection(ms, i, &redir_set))
		return (NULL);
	if (!ms->tokens[*i] || ms->tree->syntax_err)
		return (NULL);
	ms->tree->type = CMD_T;
	ms->tree->value = ms->tokens[*i];
	(1) && (ms->tree->left = NULL, ms->tree->right = NULL);
	(1) && (redir_set = 0);
	if (ms->tokens[*i] && !check_token_op(ms->tokens[*i])
		&& count_args(ms->tokens + *i))
		check_args(ms->tree, ms->tokens + *i, count_args(ms->tokens + *i));
	if (check_redir_at_end(ms, i, &redir_set))
		return (NULL);
	if (ms->tree->syntax_err == 1)
		return (NULL);
	return (ms->tree);
}
