/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:35:38 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/25 10:35:07 by abadouab         ###   ########.fr       */
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

static void	increase_shelvl(t_minishell *ms)
{
	int		num;
	char	*str;
	char	*shl;

	shl = get_env_val(ms, "SHLVL");
	if (!shl)
		return (environment_add(ms, &ms->env,
			ft_strdup(&ms->alloc, "SHLVL"), ft_strdup(&ms->alloc, "1")));
	num = ft_atoi(shl) + 1;
	str = ft_itoa(&ms->alloc, num);
	modify_env_val(ms, "SHLVL", str);
}

static void	create_environment(t_minishell *ms)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!search_env_var(ms->env, "PWD"))
		environment_add(ms, &ms->env, ft_strdup(&ms->alloc, "PWD"), NULL);
	modify_env_val(ms, "PWD", path);
	if (!search_env_var(ms->env, "SHLVL"))
		environment_add(ms, &ms->env, ft_strdup(&ms->alloc, "SHLVL"),
			ft_strdup(&ms->alloc, "0"));
	if (!search_env_var(ms->env, "_"))
		environment_add(ms, &ms->env, ft_strdup(&ms->alloc, "_"), NULL);
	modify_env_val(ms, "_", ft_strdup(&ms->alloc, "./minishell"));
	if (!search_env_var(ms->env, "OLDPWD"))
		environment_add(ms, &ms->env, "OLDPWD", NULL);
	free(path);
}

void	environment_init(t_minishell *ms, char **env)
{
	ft_bzero(ms, sizeof(t_minishell));
	if (!env)
		create_environment(ms);
	while (env && *env)
	{
		environment_add(ms, &ms->env,
			ft_substr(&ms->alloc, *env, 0, strlen_set(*env, '=')),
			ft_substr(&ms->alloc, *env, strlen_set(*env, '=') + 1,
				ft_strlen(*env)));
		env++;
	}
	if(!search_env_var(ms->env, "PWD")
		|| !search_env_var(ms->env, "SHLVL")
		|| !search_env_var(ms->env, "OLDPWD"))
		create_environment(ms);
	(ms->saved = get_env_val(ms, "PWD"), increase_shelvl(ms),
		ms->tilde = get_env_val(ms, "HOME"));
}
