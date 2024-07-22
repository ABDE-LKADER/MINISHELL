/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:45:58 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/22 18:17:21 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fds	save_fds(void)
{
	t_fds	fds;

	fds.std_in = dup(STDIN_FILENO);
	fds.std_out = dup(STDIN_FILENO);
	if (fds.std_in == -1 || fds.std_out == -1)
		perror("dup");
	return (fds);
}

void	restore_fds(t_fds fds)
{
	if (dup2(fds.std_in, STDIN_FILENO) == -1
		|| dup2(fds.std_out, STDOUT_FILENO) == -1)
		perror("dup2");
	if (close(fds.std_in) == -1 || close(fds.std_out) == -1)
		perror("close");
}

int	redir_to_dev_null(t_minishell *ms)
{
	int		null;

	null = open("/dev/null", O_RDWR);
	if (null == ERROR)
		return (error_handler(ms, "/dev/null"), ERROR);
	else if (dup2(null, STDOUT_FILENO) == ERROR
		|| dup2(null, STDIN_FILENO) == ERROR)
		perror("dup2");
	close(null);
	return (TRUE);
}

bool	wildcards_ambiguous(t_minishell *ms, char *name)
{
	int		len;
	char	**wildcards;

	wildcards = wildcards_expander(ms, name);
	len = -1;
	while (wildcards[++len])
		;
	if (len == 1)
		return (FALSE);
	return (TRUE);
}

bool	check_ambiguous_redir(t_minishell *ms, t_redirection redirection,
	char *name)
{
	int		find;
	char	*hold;
	char	*expand;

	(TRUE) && (find = FALSE, hold = name,
		expand = splite_to_expand(ms, hold, FALSE));
	if (ft_strchr(expand, '*') && wildcards_ambiguous(ms, expand))
		return (TRUE);
	if (redirection == HERE_DOC_T || !ft_strchr(name, '$'))
		return (FALSE);
	while (*name && *name != '\'' && *name != '\"')
		name++;
	if (*name && (*name == '\'' || *name == '\"'))
	{
		while (*name)
		{
			(*name == '$') && (find = TRUE);
			if (find && (*name == '\'' || *name == '\"'))
				return (FALSE);
			name++;
		}
	}
	if (ft_strchr(expand, ' '))
		return (TRUE);
	return (FALSE);
}
