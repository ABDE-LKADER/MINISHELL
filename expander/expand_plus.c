/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_plus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/20 14:50:24 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_qoutes(t_minishell *ms, char *value)
{
	if (*value == '\'' || *value == '\"')
		return (value++, ft_substr(&ms->leaks, value, 0,
				ft_strlen(value) - 1));
	return (value);
}

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
