/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/20 08:42:02 by abadouab         ###   ########.fr       */
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

	(TRUE) && (new = NULL, op = TRUE, expand = splite_use_qoutes(ms, arg));
	while (expand)
	{
		(!option && (*expand->value == '\'' || *expand->value == '\"'))
			&& (option = TRUE);
		(expand->next && (*expand->next->value == '\''
				|| *expand->next->value == '\"')) && (op = FALSE);
		(status) && (expand->value = splite_to_expand(ms, expand->value, op));
		(option) && (expand->value = remove_qoutes(ms, expand->value));
		new = ft_strjoin(&ms->leaks, new, expand->value);
		(TRUE) && (expand = expand->next, op = TRUE);
	}
	return (new);
}

void	expanding(t_minishell *ms, t_tree *tree)
{
	int		index;

	if (!tree->value)
		return ;
	index = -1;
	while (tree->args[++index])
	{
		if (*tree->args[index] == '~')
			tree->args[index] = tilde_expander(ms, tree->args[index]);
		tree->args[index] = splite_mult_args(ms, tree->args[index], TRUE, FALSE);

		// join_doubles(ms, tree, split_args(&ms->leaks, tree->args[index],
		// 	" \t\n"), &index);

		if (ft_strchr(tree->args[index], '*'))
			join_doubles(ms, tree, wildcards_expander(ms, tree->args[index]),
				&index);
	}
	while (*tree->args && !**tree->args)
		tree->args++;
	tree->value = *tree->args;
}
