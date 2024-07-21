/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/21 20:12:05 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expand	*splite_use_qoutes(t_minishell *ms, char *arg)
{
	char		*new;
	int			index;
	int			start;
	int			qoutes;
	t_expand	*expand;

	(TRUE) && (index = FALSE, start = FALSE, new = NULL, expand = NULL);
	while (arg[index])
	{
		(TRUE) && (start = index, qoutes = FALSE);
		(arg[index] == '\'' && !qoutes) && (qoutes = 1, index++);
		(arg[index] == '\"' && !qoutes) && (qoutes = 2, index++);
		while ((qoutes == 1 && arg[index] && arg[index] != '\'')
			|| (qoutes == 2 && arg[index] && arg[index] != '\"')
			|| (!qoutes && arg[index] && arg[index] != '\''
				&& arg[index] != '\"'))
			index++;
		if ((qoutes == 1 && arg[index] == '\'')
			|| (qoutes == 2 && arg[index] == '\"'))
			index++;
		expand_add(ms, &expand, ft_substr(&ms->leaks, arg, start,
				index - start));
	}
	return (expand);
}

char	*splite_mult_args(t_minishell *ms, char *arg, bool status, bool option)
{
	bool		op;
	char		*new;
	t_expand	*expand;

	(TRUE) && (new = NULL, op = FALSE, expand = splite_use_qoutes(ms, arg));
	while (expand)
	{
		(!option && (*expand->value == '\'' || *expand->value == '\"'))
			&& (option = TRUE);
		(expand->next && (*expand->next->value == '\''
				|| *expand->next->value == '\"')) && (op = TRUE);
		(status) && (expand->value = splite_to_expand(ms, expand->value, op));
		convert_to_eot(expand);
		(option) && (expand->value = remove_qoutes(ms, expand->value));
		new = ft_strjoin(&ms->leaks, new, expand->value);
		(TRUE) && (expand = expand->next, op = FALSE);
	}
	return (new);
}

void	expanding(t_minishell *ms, t_tree *tree)
{
	int	index;
	int	option;

	if (!tree->value)
		return ;
	(TRUE) && (index = -1, option = FALSE);
	while (tree->args[++index])
	{
		(*tree->args[index] == '*') && (option = TRUE);
		if (*tree->args[index] == '~')
			tree->args[index] = tilde_expander(ms, tree->args[index]);
		tree->args[index] = splite_mult_args(ms, tree->args[index], TRUE, FALSE);
		join_doubles(ms, tree, ft_split(&ms->leaks, tree->args[index],
			EOT), &index);
		if (option && ft_strchr(tree->args[index], '*'))
			join_doubles(ms, tree, wildcards_expander(ms, tree->args[index]),
				&index);
	}
	tree->value = *tree->args;
}
