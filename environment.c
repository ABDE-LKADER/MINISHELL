/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:35:38 by abadouab          #+#    #+#             */
/*   Updated: 2024/06/05 11:40:26 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	environment_add(t_minishell *ms, t_environ **env,
		void *var, void *val)
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

void	sort_export_vars(t_environ **export)
{
	size_t		len;
	void		*var;
	void		*val;
	t_environ	*first;
	t_environ	*second;

	(TRUE) && (len = 0, first = *export);
	while (first)
	{
		second = first->next;
		while (second)
		{
			len = ft_strlen(first->var);
			if (len < ft_strlen(second->var))
				len = ft_strlen(second->var);
			if (ft_strncmp(first->var, second->var, len) > 0)
			{
				(TRUE) && (var = first->var, val = first->val);
				(TRUE) && (first->var = second->var, first->val = second->val);
				(TRUE) && (second->var = var, second->val = val);
			}
			second = second->next;
		}
		first = first->next;
	}
}

void	environment_init(t_minishell *ms, char **env)
{
	t_environ	*loop;

	ft_bzero(ms, sizeof(t_minishell));
	while (*env)
	{
		environment_add(ms, &ms->env,
			ft_substr(&ms->alloc, *env, 0, strlen_set(*env, '=')),
			ft_substr(&ms->alloc, *env, strlen_set(*env, '=') + 1,
				ft_strlen(*env)));
		if (ft_strncmp(*env, "_=", strlen_set(*env, '=')))
			environment_add(ms, &ms->export,
				ft_substr(&ms->alloc, *env, 0, strlen_set(*env, '=')),
				ft_substr(&ms->alloc, *env, strlen_set(*env, '=') + 1,
					ft_strlen(*env)));
		env++;
	}
	sort_export_vars(&ms->export);
	loop = ms->export;
	while (loop)
	{
		loop->var = ft_strjoin(&ms->alloc, "declare -x ", loop->var);
		loop->val = ft_strjoin(&ms->alloc, "\"", loop->val);
		loop->val = ft_strjoin(&ms->alloc, loop->val, "\"");
		loop = loop->next;
	}
}
