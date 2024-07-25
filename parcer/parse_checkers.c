/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:39:32 by abbaraka          #+#    #+#             */
/*   Updated: 2024/07/25 11:28:11 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_token_op(char *token)
{
	char	*operators[4];
	int		i;

	operators[0] = "|";
	operators[1] = "||";
	operators[2] = "&&";
	operators[3] = NULL;
	if (!token)
		return (0);
	i = 0;
	while (operators[i])
	{
		if (ft_strncmp(token, operators[i], ft_strlen(token)) == 0
			&& ft_strlen(token) == ft_strlen(operators[i]))
			return (1);
		i++;
	}
	return (0);
}

void	set_op(t_tree *tree, char *token)
{
	if (!ft_strncmp(token, "|", ft_strlen(token)))
		tree->type = PIPE_T;
	else if (!ft_strncmp(token, "&&", ft_strlen(token))
		&& ft_strlen(token) == ft_strlen("&&"))
		tree->type = AND_T;
	else if (!ft_strncmp(token, "||", ft_strlen(token))
		&& ft_strlen(token) == ft_strlen("||"))
		tree->type = OR_T;
}

int	check_closed_quotes(t_minishell *ms, int i, int j)
{
	char	quotes;

	i = 0;
	while (ms->tokens[i])
	{
		(1) && (j = 0, quotes = -1);
		while (ms->tokens[i][j])
		{
			if (ms->tokens[i][j] == '"' || ms->tokens[i][j] == '\'')
			{
				if (quotes > -1 && ms->tokens[i][j] == quotes)
					quotes = -1;
				else if (quotes == -1)
					quotes = ms->tokens[i][j];
			}
			j++;
		}
		if (quotes > -1 && ms->tree && ms->tree->dis_error == 0)
			return (syntax_err(ms, NULL,
					"syntax error: unexpected end of file", 258), 1);
		i++;
	}
	return (0);
}

t_tree	*ft_treelast(t_tree *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_treeadd_back(t_tree **lst, t_tree *new)
{
	t_tree	*node;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	node = *lst;
	node = ft_treelast(node);
	node->next = new;
}
