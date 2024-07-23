/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_val.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/23 16:18:46 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	only_var(t_minishell *ms, char *arg)
{
	char	**hold;

	if (*arg != '$')
		return (TRUE);
	hold = ft_split(&ms->leaks, arg, '$');
	while (*arg == '$')
		arg++;
	if (!*arg)
		return (TRUE);
	while (*arg)
	{
		if (!ft_isalnum(*arg) && *arg != '_' && *arg != '$')
			return (TRUE);
		arg++;
	}
	while (*hold)
	{
		if (get_env_val(ms, *hold))
			return (TRUE);
		hold++;
	}
	return (FALSE);
}

char	*expand_val(t_minishell *ms, char *value)
{
	t_environ	*loop;

	if (!ft_strncmp(value, "$$", ft_strlen(value))
		&& ft_strlen("$$") == ft_strlen(value))
		return ("000000");
	if (!ft_strncmp(value, "$?", ft_strlen(value))
		&& ft_strlen("$?") == ft_strlen(value))
		return (ft_itoa(&ms->leaks, ms->exit_status));
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
