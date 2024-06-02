/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:39:11 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/02 10:05:35 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*parse_side(t_minishell *ms, int *i)
{
	t_tree	*exp;

	if (ms->tokens[*i]
		&& ft_strncmp(ms->tokens[*i], ")", ft_strlen(ms->tokens[*i])) == 0)
		return (syntax_err("syntax error near unexpected token `)'", 0), NULL);
	else if (ms->tokens[*i]
		&& ft_strncmp(ms->tokens[*i], "(", ft_strlen(ms->tokens[*i])) == 0)
	{
		(*i)++;
		exp = parse_exp(ms, i, 0);
		// if (tokens[*i + 1]
		// 	&& ft_strncmp(tokens[*i + 1], "(", ft_strlen(tokens[*i + 1])) == 0)
		// 	return (syntax_err("syntax error near unexpected token `('", 0)
		// 		, NULL);
		return (exp);
	}
	return (parse_simple_command(&ms->leaks, ms->tokens, i));
}

t_tree	*make_tree(t_allocate **leaks, t_tree *left, t_tree *right, char *op)
{
	t_tree	*node;

	node = allocate(leaks, 1, sizeof(t_tree));
	set_op(node, op);
	if (ft_strncmp(op, "|", ft_strlen(op)) == 0
		&& ft_strlen(op) == ft_strlen("|"))
		node->type = PIPE_T;
	if (ft_strncmp(op, "||", ft_strlen(op)) == 0
		&& ft_strlen(op) == ft_strlen("||"))
		node->type = OR_T;
	if (ft_strncmp(op, "&&", ft_strlen(op)) == 0
		&& ft_strlen(op) == ft_strlen("&&"))
		node->type = AND_T;
	node->value = op;
	node->left = left;
	node->right = right;
	return (node);
}

int	check_if_prec(char *token)
{
	if ((ft_strncmp(token, "||", ft_strlen(token)) == 0
			&& ft_strlen(token) == ft_strlen("||"))
		|| (ft_strncmp(token, "&&", ft_strlen(token)) == 0
			&& ft_strlen(token) == ft_strlen("&&")))
		return (0);
	return (1);
}

t_tree	*parse_exp(t_minishell *ms, int *i, int min_pr)
{
	char		*op;
	t_tree		*left;
	t_tree		*right;

	left = parse_side(ms, i);
	if (!left)
		return (NULL);
	if (!ms->tokens[*i])
		return (left);
	if (ms->tokens[*i] && check_token_op(ms->tokens[*i]))
		(*i)--;
	while (ms->tokens[*i] && ms->tokens[*i + 1]
		&& check_token_op(ms->tokens[*i + 1])
		&& min_pr <= check_if_prec(ms->tokens[*i + 1]))
	{
		op = ms->tokens[*i + 1];
		(*i) += 2;
		if (!ms->tokens[*i] || check_token_op(ms->tokens[*i]))
			return (syntax_err("syntax error", 0), NULL);
		right = parse_exp(ms, i, check_if_prec(op) + 1);
		left = make_tree(&ms->leaks, left, right, op);
	}
	return (left);
}

t_tree	*parse(t_minishell *ms)
{
	int			i;
	int			j;

	if (!ms->tokens || !ms->tokens[0])
		return (NULL);
	i = 0;
	j = 0;
	if (check_closed_quotes(ms->tokens, i, j))
		return (NULL);
	ms->tree = allocate(&ms->leaks, 1, sizeof(t_tree));
	ms->tree = parse_exp(ms, &i, 0);
	if (ms->tree)
	{
		if (ms->tree->right)
		{
			printf("             %s     \n", ms->tree->value);
			printf("           /    \\   \n");
			printf("          /      \\   \n");
			if (ms->tree->type)
			{
				printf("        %s  ", ms->tree->left->value);
				if (ms->tree->right)
					printf("      %s  \n", ms->tree->right->value);
				if (check_token_op(ms->tree->left->value))
				{
					printf("      /   \\   \n");
					printf("     /     \\   \n");
					printf("   %s   ", ms->tree->left->left->value);
					printf("   %s   \n", ms->tree->left->right->value);
					// if (check_token_op(ms->tree->left->left->value))
					// {
					// 	printf(" /   \\   \n");
					// 	printf(" /     \\   \n");
					// 	printf(" %s   ", ms->tree->left->left->left->value);
					// 	printf("  %s   \n", ms->tree->left->left->right->value);
					// }
				}
			}
		}
		else
			printf("Tree left:%s\n", ms->tree->value);
	}
	return (ms->tree);
}
