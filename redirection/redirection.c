/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:45:58 by abadouab          #+#    #+#             */
/*   Updated: 2024/06/11 20:00:56 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_redir(t_minishell *ms, int fd, bool option)
{
	if (!option)
		fd = here_doc_expander(ms, fd);
	if (dup2(fd, STDIN_FILENO) == -1)
		perror("dup2");
	close(fd);
}

static void	in_redirection(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		perror("open");
	else if (dup2(fd, STDIN_FILENO) == -1)
		perror("dup2");
	close(fd);
}

static void	out_redirection(char *file)
{
	int		fd;

	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd == -1)
		perror("open");
	else if (dup2(fd, STDOUT_FILENO) == -1)
		perror("dup2");
	close(fd);
}

static void	append_out_redir(char *file)
{
	int		fd;

	fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (fd == -1)
		perror("open");
	else if (dup2(fd, STDOUT_FILENO) == -1)
		perror("dup2");
	close(fd);
}

void	redirection(t_minishell *ms, t_tree *tree)
{
	int		index;

	index = -1;
	while (++index < tree->redir_index)
	{
		if (tree->redir[index].redirection == IN_RED_T)
			in_redirection(tree->redir[index].redir_name);
		if (tree->redir[index].redirection == OUT_RED_T)
			out_redirection(tree->redir[index].redir_name);
		if (tree->redir[index].redirection == OUT_RED_APPEND_T)
			append_out_redir(tree->redir[index].redir_name);
		if (tree->redir[index].redirection == HERE_DOC_T)
			here_doc_redir(ms, tree->redir[index].fd,
				tree->redir[index].set_expand);
	}
}
