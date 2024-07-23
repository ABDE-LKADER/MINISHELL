/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:35:38 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/23 06:55:13 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	environment_add(t_minishell *ms, t_environ **env, void *var, void *val)
{
	t_environ	*new;
	t_environ	*node;

	new = allocate(&ms->alloc, 1, sizeof(t_environ));
	if (!new)
		cleanup_handler(ms);
	new->var = var;
	new->val = val;
	new->next = NULL;
	if (!*env)
	{
		*env = new;
		return ;
	}
	node = *env;
	while (node->next)
		node = node->next;
	node->next = new;
}

void	increase_shelvl(t_minishell *ms)
{
	int		num;
	char	*str;

	num = ft_atoi(get_env_val(ms, "SHLVL")) + 1;
	str = ft_itoa(&ms->alloc, num);
	modify_env_val(ms, "SHLVL", str);
}

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

void	environment_init(t_minishell *ms, char **env, int ac, char **av)
{
	if (ac != 1 && av)
		(ft_putendl_fd("./minishell <empty>", 2), exit(EXIT_FAILURE));
	ft_bzero(ms, sizeof(t_minishell));
	if (!env || !*env)
	{
		environment_add(ms, &ms->env,
			ft_strdup(&ms->alloc, "PWD"), getcwd(NULL, 0));
		environment_add(ms, &ms->env,
			ft_strdup(&ms->alloc, "SHLVL"), ft_strdup(&ms->alloc, "0"));
		environment_add(ms, &ms->env,
			ft_strdup(&ms->alloc, "_"), ft_strdup(&ms->alloc, "./minishell"));
	}
	else
	{
		while (*env)
		{
			environment_add(ms, &ms->env,
				ft_substr(&ms->alloc, *env, 0, strlen_set(*env, '=')),
				ft_substr(&ms->alloc, *env, strlen_set(*env, '=') + 1,
					ft_strlen(*env)));
			env++;
		}
		if (get_env_val(ms, "OLDPWD") == NULL)
			environment_add(ms, &ms->env, "OLDPWD", NULL);	
	}
	increase_shelvl(ms);
}
