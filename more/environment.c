/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:35:38 by abadouab          #+#    #+#             */
/*   Updated: 2024/06/11 19:53:44 by abadouab         ###   ########.fr       */
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

void	environment_init(t_minishell *ms, char **env, int ac, char **av)
{
	if (ac != 1 && av)
		(ft_putendl_fd("./minishell <empty>", 2), exit(EXIT_FAILURE));
	ft_bzero(ms, sizeof(t_minishell));
	while (*env)
	{
		environment_add(ms, &ms->env,
			ft_substr(&ms->alloc, *env, 0, strlen_set(*env, '=')),
			ft_substr(&ms->alloc, *env, strlen_set(*env, '=') + 1,
				ft_strlen(*env)));
		env++;
	}
	environment_add(ms, &ms->env, "OLDPWD", NULL);
}
