/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:12:51 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/27 17:34:06 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_fds(t_tree *tree)
{
	int		index;

	index = -1;
	while (++index < tree->redir_index)
	{
		if (tree->redir[index].fd != -1)
			close(tree->redir[index].fd);
	}
}

int	check_par(char *s)
{
	int		i;
	int		level;
	int		quotes;

	(TRUE) && (i = -1, level = 0);
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			(TRUE) && (quotes = s[i], i++);
			while (s[i] && s[i] != quotes)
				i++;
		}
		if (s[i] == '\0')
			break ;
		if (s[i] == '(')
			level++;
		if (s[i] == '(' && s[i + 1] == ')')
			return (1);
		if (s[i] == ')')
			level--;
	}
	if (level)
		return (1);
	return (0);
}
