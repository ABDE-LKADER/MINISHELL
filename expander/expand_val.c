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
		if (!ft_strncmp(loop->var, arg, ft_strlen(arg)) 
			&& ft_strlen(arg) == ft_strlen(loop->var))
			return (loop->val);
		loop = loop->next;
	}
	return (ft_strdup(&ms->leaks, ""));
}
