/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:56:53 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/24 10:27:26 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	valid_identifier(char *str, int len)
{
	int		index;

	index = -1;
	while (++index < len)
	{
		if (index + 1 == len && str[index] == '+')
			return (TRUE);
		if (!ft_isalnum(str[index]) && str[index] != '_')
			return (FALSE);
	}
	return (TRUE);
}

bool	search_env_var(t_environ *env, char *to_find)
{
	while (env)
	{
		if (!ft_strncmp(env->var, to_find, ft_strlen(to_find))
			&& ft_strlen(to_find) == ft_strlen(env->var))
			return (TRUE);
		env = env->next;
	}
	return (FALSE);
}

void	modify_env_val(t_minishell *ms, char *env_var, char *val)
{
	t_environ	*tmp;

	tmp = ms->env;
	if (!val)
		return ;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, env_var, ft_strlen(tmp->var)) == 0)
		{
			tmp->val = ft_strdup(&ms->alloc, val);
			return ;
		}
		tmp = tmp->next;
	}
}

char	*get_env_val(t_minishell *ms, char *s)
{
	t_environ	*tmp;

	tmp = ms->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, s, ft_strlen(tmp->var)) == 0)
			return (tmp->val);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_env(t_minishell *ms, t_environ *env)
{
	while (env)
	{
		if (env->val)
			ft_printf("%s=%s\n", env->var, env->val);
		env = env->next;
	}
	ms->exit_status = 0;
}
