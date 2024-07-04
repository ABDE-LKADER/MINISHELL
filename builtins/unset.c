/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: |||||||| <||||||||@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by ||||||||          #+#    #+#             */
/*   Updated: 2024/06/11 14:46:14 by ||||||||         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_unset_target(t_environ **env, char *to_find)
{
	t_environ	*current;
	t_environ	*previous;

	current = *env;
	previous = NULL;
	while (current)
	{
		if (!ft_strncmp(current->var, to_find, ft_strlen(to_find))
			&& ft_strlen(current->var) == ft_strlen(to_find))
		{
			if (!previous)
				*env = current->next;
			else
				previous->next = current->next;
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void	ft_unset(t_minishell *ms, char **args)
{
	int	index;

	index = 0;
	while (args[++index])
		env_unset_target(&ms->env, args[index]);
	ms->exit_status = 0;
}
