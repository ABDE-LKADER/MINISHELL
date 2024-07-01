/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darkab <darkab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:39:37 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/13 21:13:17 by darkab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_redir(t_minishell *ms, int *i)
{
	t_tree	*node;
	char	**tokens;

	(TRUE) && (node = ms->tree, tokens = ms->tokens, ms->tree->redir_ex = true,
		node->redir[node->redir_index].set_expand = 0);
	if (ft_strncmp(tokens[*i], ">", ft_strlen(tokens[*i])) == 0)
		(TRUE) && (node->redir[node->redir_index].redirection = OUT_RED_T,
			node->redir[node->redir_index].fd = -1);
	else if (ft_strncmp(tokens[*i], "<", ft_strlen(tokens[*i])) == 0)
		(TRUE) && (node->redir[node->redir_index].redirection = IN_RED_T,
			node->redir[node->redir_index].fd = -1);
	else if (ft_strncmp(tokens[*i], ">>", ft_strlen(tokens[*i])) == 0)
		(TRUE) && (node->redir[node->redir_index].redirection =
			OUT_RED_APPEND_T, node->redir[node->redir_index].fd = -1);
	else if (ft_strncmp(tokens[*i], "<<", ft_strlen(tokens[*i])) == 0
		&& g_catch_signals == 0)
		(TRUE) && (node->redir[node->redir_index].redirection = HERE_DOC_T,
		node->redir[node->redir_index].fd = ft_open_here_doc(ms,
		tokens[*i + 1], node));
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
		else if (tokens[j] && !check_if_operator(tokens[j])
			&& !check_token_op(tokens[j]))
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
		return (syntax_err(ms, NULL, "syntax error", 258), 1);
	ms->tree = allocate(&ms->leaks, 1, sizeof(t_tree));
	if (!ms->tree)
		error_handler(ms);
	(1) && (*redir_set = 0, ms->tree->redir_index = 0,
	ms->tree->syntax_err = 0, ms->tree->redir_ex = false);
	ms->tree->redir = allocate(&ms->leaks, count_redir(ms->tokens) + 1,
			sizeof(t_redir));
	if (!ms->tree->redir)
		error_handler(ms);
	ms->tree->args = allocate(&ms->leaks, count_args(ms->tokens + *i) + 1,
			sizeof(char *));
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
	if (ms->tree->syntax_err)
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
