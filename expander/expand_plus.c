/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_plus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/25 06:25:23 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	convert_to_eot(t_expand *expand)
{
	int		index;

	index = -1;
	while (expand->value[++index])
	{
		if (is_whitespace(expand->value[index]))
			expand->value[index] = EOT;
	}
}

char	*remove_qoutes(t_minishell *ms, char *value)
{
	int	len;

	len = ft_strlen(value) - 1;
	if ((*value == '\'' && value[len] == '\'')
		|| (*value == '\"' && value[len] == '\"'))
		return (value++, ft_substr(&ms->leaks, value, 0,
				ft_strlen(value) - 1));
	return (value);
}

bool	expand_option(char *value, char *sp, int option)
{
	if ((option == FALSE || option == ERROR)
		&& !ft_strncmp("$", sp, ft_strlen(sp)))
		return (FALSE);
	if (option != ERROR && *value == '\'')
		return (FALSE);
	return (TRUE);
}

bool	split_expansion_checker(t_minishell *ms)
{
	int		index;

	if (!ms->to_check)
		return (FALSE);
	index = 0;
	while (ms->to_check[index])
		index++;
	if (*ms->current >= index)
		return (FALSE);
	if ((ft_strncmp(*ms->to_check, "export", ft_strlen("export"))
			&& ft_strlen(*ms->to_check) == ft_strlen("export"))
		|| !ft_strchr(ms->to_check[*ms->current], '=')
		|| !ft_strchr(ms->to_check[*ms->current], '$'))
		return (TRUE);
	(TRUE) && (index = -1);
	while (ms->to_check[*ms->current][++index] != '=')
	{
		if (ms->to_check[*ms->current][index] == '$')
			return (TRUE);
	}
	return (FALSE);
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
