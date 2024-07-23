/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:45:58 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/23 10:57:23 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_redir(t_minishell *ms, int fd, bool option)
{
	if (!option)
		fd = here_doc_expander(ms, fd);
	if (dup2(fd, STDIN_FILENO) == ERROR)
		perror("dup2");
	close(fd);
}

static int	in_redirection(t_minishell *ms, char *file)
{
	int		fd;

	file = splite_mult_args(ms, file, TRUE, TRUE);
	fd = open(file, O_RDONLY, 0777);
	if (fd == ERROR)
		return (error_handler(ms, file), ERROR);
	else if (dup2(fd, STDIN_FILENO) == ERROR)
		perror("dup2");
	close(fd);
	return (TRUE);
}

static int	out_redirection(t_minishell *ms, char *file)
{
	int		fd;

	file = splite_mult_args(ms, file, TRUE, TRUE);
	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd == ERROR)
		return (error_handler(ms, file), ERROR);
	else if (dup2(fd, STDOUT_FILENO) == ERROR)
		perror("dup2");
	close(fd);
	return (TRUE);
}

static int	append_out_redir(t_minishell *ms, char *file)
{
	int		fd;

	file = splite_mult_args(ms, file, TRUE, TRUE);
	fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (fd == ERROR)
		return (error_handler(ms, file), ERROR);
	else if (dup2(fd, STDOUT_FILENO) == ERROR)
		perror("dup2");
	close(fd);
	return (TRUE);
}

int	redirection(t_minishell *ms, t_tree *tree)
{
	int		index;
	int		status;

	(TRUE) && (index = -1, status = TRUE);
	while (++index < tree->redir_index && status == 1)
	{
		if (check_ambiguous_redir(ms, tree->redir[index].redirection,
				tree->redir[index].redir_name))
			return (status = redir_to_dev_null(ms),
				syntax_err(ms, tree->redir[index].redir_name, AMBG, 1),
				ms->exit_status = 1, -1);
		if (tree->redir[index].redirection == IN_RED_T)
			status = in_redirection(ms, tree->redir[index].redir_name);
		if (tree->redir[index].redirection == OUT_RED_T)
			status = out_redirection(ms, tree->redir[index].redir_name);
		if (tree->redir[index].redirection == OUT_RED_APPEND_T)
			status = append_out_redir(ms, tree->redir[index].redir_name);
		if (tree->redir[index].redirection == HERE_DOC_T)
			here_doc_redir(ms, tree->redir[index].fd,
				tree->redir[index].set_expand);
	}
	return (status);
}
