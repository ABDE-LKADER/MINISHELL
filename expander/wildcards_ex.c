/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_ex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/19 17:33:04 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_doubles(t_minishell *ms, t_tree *tree, char **join, int *index)
{
	int		len;
	int		_len;
	char	**new;

	if (!join || !*join)
		return ;
	(TRUE) && (len = 0, _len = 0);
	while (tree->args[len])
		len++;
	while (join[_len])
		_len++;
	new = allocate(&ms->leaks, len + _len + 1, sizeof(char *));
	if (!new)
		cleanup_handler(ms);
	(TRUE) && (len = -1, _len = (*index) + 1);
	while (++len < _len - 1 && tree->args[len])
		new[len] = tree->args[len];
	while (*join)
		(TRUE) && (new[len] = *join++, len++);
	(*index) = len - 1;
	while (tree->args[_len])
		new[len++] = tree->args[_len++];
	(TRUE) && (new[len] = NULL);
	tree->args = new;
}

char	**convert_to_array(t_minishell *ms, t_expand *expand)
{
	int			len;
	char		**new;
	t_expand	*loop;

	(TRUE) && (len = 0, loop = expand);
	while (loop)
		(TRUE) && (len++, loop = loop->next);
	new = allocate(&ms->leaks, len + 1, sizeof(char *));
	if (!new)
		cleanup_handler(ms);
	(TRUE) && (len = 0, loop = expand);
	while (expand)
		(TRUE) && (new[len++] = expand->value,
			expand = expand->next);
	new[len] = NULL;
	return (new);
}

bool	pattern_matching(char *name, char *pattern)
{
	int		n_len;
	int		p_len;

	n_len = ft_strlen(name);
	p_len = ft_strlen(pattern);
	if (!ft_strncmp(pattern, "*", p_len) && *name != '.')
		return (TRUE);
	if (!ft_strncmp(pattern, "*", p_len) && *name == '.')
		return (FALSE);
	if (*pattern != '*' && *pattern != *name)
		return (FALSE);
	if (pattern[--p_len] != '*' && pattern[p_len] != name[--n_len])
		return (FALSE);
	while (*name)
	{
		while (*pattern == '*')
			pattern++;
		if (*name++ == *pattern)
			pattern++;
		while (*pattern == '*')
			pattern++;
	}
	if (!*pattern)
		return (TRUE);
	return (FALSE);
}

char	**wildcards_expander(t_minishell *ms, char *arg)
{
	DIR				*dir;
	t_expand		*expand;
	struct dirent	*entries;

	(TRUE) && (expand = NULL, dir = opendir("."));
	if (!dir)
	{
		perror("opendir");
		return (NULL);
	}
	entries = readdir(dir);
	while (entries)
	{
		if (pattern_matching((char *)entries->d_name, arg))
			expand_add(ms, &expand, ft_strdup(&ms->leaks, entries->d_name));
		entries = readdir(dir);
	}
	return (closedir(dir), convert_to_array(ms, expand));
}
