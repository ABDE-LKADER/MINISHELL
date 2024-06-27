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

bool	expand_option(char *value, char *sp)
{
	if (!ft_strncmp("$", sp, ft_strlen(sp)))
		return (FALSE);
	if (*value == '\'')
		return (FALSE);
	return (TRUE);
}

char	*tilde_expander(t_environ *env)
{
	t_environ	*loop;

	loop = env;
	while (loop)
	{
		if (!ft_strncmp(loop->var, "HOME", ft_strlen(loop->var))
			&& ft_strlen(loop->var) == ft_strlen("HOME"))
			return (loop->val);
		loop = loop->next;
	}
	return (NULL);
}

char	*wildcards_expander(t_minishell *ms)
{
	DIR				*dir;
	char			*new;
	struct dirent	*entries;
	t_expand		*expand;

	new = NULL;
	dir  = opendir(".");
	if (!dir)
		return (perror("opendir"), NULL);
	entries = readdir(dir);
	while (entries)
	{
		if (*entries->d_name != '.')
		{
			if (new)
				new = ft_strjoin(&ms->leaks, new, " ");
			new = ft_strjoin(&ms->leaks, new, entries->d_name);
		}
		entries = readdir(dir);
	}
	return (closedir(dir), new);
}
