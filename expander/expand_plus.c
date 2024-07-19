/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_plus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/19 17:06:46 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	expand_option(char *value, char *sp, int option)
{
	if (option && !ft_strncmp("$", sp, ft_strlen(sp)))
		return (FALSE);
	if (!option && *value == '\'')
		return (FALSE);
	return (TRUE);
}

char	*tilde_expander(t_minishell *ms, char *value)
{
	t_environ	*loop;

	loop = ms->env;
	while (loop)
	{
		if (!ft_strncmp(loop->var, "HOME", ft_strlen(loop->var))
			&& ft_strlen(loop->var) == ft_strlen("HOME"))
		{
			if (!ft_strncmp("~", value, ft_strlen(value)))
				return (loop->val);
			if (*(value + 1) == '/')
				return (ft_strjoin(&ms->leaks, loop->val, value + 1));
			return (value);
		}
		loop = loop->next;
	}
	return (value);
}
