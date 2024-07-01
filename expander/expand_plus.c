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

bool	expand_option(char *value, char *sp, bool option)
{
	if (option && !ft_strncmp("$", sp, ft_strlen(sp)))
		return (FALSE);
	if (*value == '\'')
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

char	**convert_to_array(t_expand **expand)
{
	char	**new;

	return (new);
}

void	specified_wildcards(t_minishell *ms, t_expand **expand, char *value,
	DIR *dir)
{
	struct dirent	*entries;

	entries = readdir(dir);
	while (entries)
	{
		if (*entries->d_name != '.')
			;
		entries = readdir(dir);
	}
}

char	**wildcards_expander(t_minishell *ms, char **args)
{
	DIR			*dir;
	t_expand	*expand;

	(TRUE) && (expand = NULL, dir  = opendir("."));
	if (!dir)
	{
		perror("opendir");
		return ;
	}
	while (*args)
	{
		if (ft_strchr(*args, '*'))
			specified_wildcards(ms, &expand, *args, dir);
		else
			expand_add(ms, &expand, *args);
		args++;
	}
	return (closedir(dir), convert_to_array(expand));
}
