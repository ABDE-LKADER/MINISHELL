/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:56:53 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/23 09:56:55 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
