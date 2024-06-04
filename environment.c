/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:35:38 by abadouab          #+#    #+#             */
/*   Updated: 2024/06/04 20:25:12 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	environment_add(t_minishell *ms, t_environ **env, void *var, void *val)
{
	t_environ	*new;
	t_environ	*node;

	new = allocate(&ms->alloc, 1, sizeof(t_environ));
	if (!new)
		error_handler(ms);
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

void	environment_init(t_minishell *ms, char **env)
{
	int			index;
	t_environ	*loop;

	index = -1;
	ft_bzero(ms, sizeof(t_minishell));
	while (env[++index])
	{
		environment_add(ms, &ms->env,
			ft_substr(&ms->alloc, env[index], 0, strlen_set(env[index], '=')),
			ft_substr(&ms->alloc, env[index], strlen_set(env[index], '=') + 1,
				ft_strlen(env[index])));
		if (ft_strncmp(env[index], "_=", strlen_set(env[index], '=')))
			environment_add(ms, &ms->export,
				ft_substr(&ms->alloc, env[index], 0, strlen_set(env[index], '=')),
				ft_substr(&ms->alloc, env[index], strlen_set(env[index], '=') + 1,
					ft_strlen(env[index])));
	}
	loop = ms->export;
	while (loop)
	{
		loop->var = ft_strjoin(&ms->alloc, "declare -x ", loop->var);
		loop->val = ft_strjoin(&ms->alloc, "\"", loop->val);
		loop->val = ft_strjoin(&ms->alloc, loop->val, "\"");
		loop = loop->next;
	}
}
