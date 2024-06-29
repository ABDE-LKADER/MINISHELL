/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by abadouab          #+#    #+#             */
/*   Updated: 2024/06/11 14:46:14 by abadouab         ###   ########.fr       */
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

	(TRUE) && (index = 0, start = 0, new = NULL, expand = NULL);
	while (arg[index])
	{
		(TRUE) && (start = index, qoutes = 0);
		(arg[index] == '\''&& !qoutes) && (qoutes = 1, index++);
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

char	*remove_qoutes(t_minishell *ms, char *value)
{
	if (*value == '\'' || *value == '\"')
		return (value++, ft_substr(&ms->leaks, value, 0,
			ft_strlen(value) - 1));
	return (value);
}

char	*splite_mult_args(t_minishell *ms, char *arg)
{
	char		*new;
	t_expand	*expand;

	(TRUE) && (new = NULL, expand = splite_use_qoutes(ms, arg));
	while (expand)
	{
		expand->value = splite_to_expand(ms, expand->value);
		expand->value = remove_qoutes(ms, expand->value);
		new = ft_strjoin(&ms->leaks, new, expand->value);
		expand = expand->next;
	}
	return (new);
}

void	expanding(t_minishell *ms, t_tree *tree)
{
	int		index;
	bool	wildcards;

	if (!tree->value)
		return ;
	(TRUE) && (index = -1, wildcards = 0);
	while (tree->args[++index])
	{
		if (!ft_strncmp("~", tree->args[index], ft_strlen(tree->args[index])))
			tree->args[index] = tilde_expander(ms->env);
		else
			tree->args[index] = splite_mult_args(ms, tree->args[index]);
		(ft_strchr(tree->args[index], '*')) && (wildcards = 1);
	}
	if (wildcards)
		tree->args = wildcards_expander(ms, tree->args);
	tree->value = *tree->args;
}