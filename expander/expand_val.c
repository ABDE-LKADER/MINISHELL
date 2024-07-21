/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_val.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/20 20:41:30 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_val(t_minishell *ms, char *value)
{
	t_environ	*loop;

	if (!ft_strncmp(value, "$$", ft_strlen(value))
		&& ft_strlen("$$") == ft_strlen(value))
		return (value = ft_itoa(&ms->leaks, getpid()));
	if (!ft_strncmp(value, "$?", ft_strlen(value))
		&& ft_strlen("$?") == ft_strlen(value))
		return (value = ft_itoa(&ms->leaks, ms->exit_status));
	(TRUE) && (value++, loop = ms->env);
	if (ft_isdigit(*value))
		return (value + 1);
	while (loop)
	{
		if (!ft_strncmp(loop->var, value, ft_strlen(value))
			&& ft_strlen(value) == ft_strlen(loop->var))
		{
			if (!loop->val)
				break ;
			if (loop->val)
				return (loop->val);
		}
		loop = loop->next;
	}
	return (ft_strdup(&ms->leaks, ""));
}
