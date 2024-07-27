/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by abbaraka          #+#    #+#             */
/*   Updated: 2024/07/27 09:48:21 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_valid_identifier(char *str)
{
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

static void	env_unset_target(t_environ **env, char *to_find)
{
	t_environ	*current;
	t_environ	*previous;

	if (!ft_strncmp(to_find, "_", ft_strlen(to_find)))
		return ;
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
	while (*args)
	{
		if (((!ft_isalpha(**args) && **args != '_')
				|| !check_valid_identifier(*args)))
		{
			syntax_err(ms, *args, "not a valid identifier", 1);
			ms->exit_status = 1;
			return ;
		}
		env_unset_target(&ms->env, *args++);
	}
	ms->exit_status = 0;
}
