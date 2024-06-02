/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_checkers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:39:19 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/02 09:43:50 by abbaraka         ###   ########.fr       */
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

int	check_redirection(t_tree *node, char **tokens, int *i, int	*redir_set)
{
	if (ft_strncmp(tokens[*i], ">", ft_strlen(tokens[*i])) == 0
		|| ft_strncmp(tokens[*i], "<", ft_strlen(tokens[*i])) == 0
		|| ft_strncmp(tokens[*i], ">>", ft_strlen(tokens[*i])) == 0
		|| ft_strncmp(tokens[*i], "<<", ft_strlen(tokens[*i])) == 0)
	{
		if (!tokens[*i + 1])
			return (syntax_err("syntax error", 258), node->syntax_err = 1, 1);
		set_redir(node, tokens[*i]);
		if (check_if_operator(tokens[*i + 1]) || check_token_op(tokens[*i + 1]))
			return (syntax_err("syntax error", 258), node->syntax_err = 1, 1);
		node->redir[node->redir_index].redir_name = tokens[*i + 1];
		printf("redir file name : %s\n", node->redir[node->redir_index].redir_name);
		node->redir_index++;
		*redir_set = 1;
		(*i) += 2;
	}
	if (*redir_set == 0 && tokens[*i] && check_if_operator(tokens[*i]))
		return (syntax_err("syntax error", 258), node->syntax_err = 1, 1);
	*redir_set = 0;
	if (tokens[*i] && check_if_operator(tokens[*i])
		&& tokens[*i + 1] && !check_token_op(tokens[*i + 1]))
		check_redirection(node, tokens, i, redir_set);
	return (0);
}

int	check_redir_at_end(t_tree *node, char **tokens, int *i, int *redir_set)
{
	while (tokens[*i] && !check_token_op(tokens[*i]))
	{
		if (tokens[*i] && check_if_operator(tokens[*i]))
		{
			if (tokens[*i] && check_redirection(node, tokens, i, redir_set))
				return (1);
		}
		if (tokens[*i] && check_valid_op(tokens[*i]))
			return (syntax_err("syntax error", 258), node->syntax_err = 1, 1);
		if (!tokens[*i] || check_token_op(tokens[*i]))
			return (0);
		else
			(*i)++;
	}
	return (0);
}
