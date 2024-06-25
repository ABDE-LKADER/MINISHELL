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
		expand_add(ms, &expand, ft_substr(&ms->leaks, arg, start, index - start));
	}
	return (expand);
}

char	*splite_mult_args(t_minishell *ms, char *arg)
{
	char		*new;
	t_expand	*expand;

	(TRUE) && (new = NULL, // arg = remove_duplicate_qoutes(ms, arg),
		expand = splite_use_qoutes(ms, arg));
	while (expand)
	{
		printf("|%s|\n", expand->value);
		expand->value = splite_to_expand(ms, expand->value);
		new = ft_strjoin(&ms->leaks, new, expand->value);
		expand = expand->next;
	}
	return (new);
}

void	expanding(t_minishell *ms, char **args)
{
	int		index;

	index = -1;
	while (args[++index])
	{
		if (!ft_strncmp("~", args[index], ft_strlen(args[index])))
			args[index] = tilde_expander(ms->env);
		else if (ft_strchr(args[index], '$'))
			args[index] = splite_mult_args(ms, args[index]);
	}
}
