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

char	*expand_val(t_minishell *ms, char *arg)
{
	t_environ	*loop;

	loop = ms->env;
	while (loop)
	{
		if (!ft_strncmp(loop->var, arg, ft_strlen(arg)))
			return (loop->val);
		loop = loop->next;
	}
	return (ft_strdup(&ms->leaks, ""));
}

char	*splite_to_expand(t_minishell *ms, char *arg)
{
	int			end;
	int			start;
	char		*expand;
	t_environ	*loop;

	(TRUE) && (end = 0, start = 0);
	start = strlen_set(arg, '$');
	end = strlen_set(arg, ' ');
	expand = allocate(&ms->leaks, end - start, sizeof(char));
	loop = ms->env;
	while (loop)
	{
		if (!ft_strncmp(loop->var, arg + start + 1, end - start))
			return (loop->val);
		loop = loop->next;
	}
	return (ft_strdup(&ms->leaks, ""));
}

void	expanding(t_minishell *ms, char **args)
{
	int		index;

	index = -1;
	while (args[++index])
		args[index] = expand_val(ms, args[index]);
}
