/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_plus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/20 19:29:37 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	convert_to_eot(t_expand *expand)
{
	int		index;

	index = -1;
	if (*expand->value == '\'' || *expand->value == '\"')
		return ;
	while (expand->value[++index])
	{
		if (expand->value[index] == ' ' || expand->value[index] == '\t'
			|| expand->value[index] == '\n')
			expand->value[index] = EOT_MARKER;
	}
}

char	*remove_qoutes(t_minishell *ms, char *value)
{
	if (*value == '\'' || *value == '\"')
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
