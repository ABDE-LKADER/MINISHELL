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

void	here_doc_redir(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		(perror("dup2"), exit(EXIT_FAILURE));
	}
	close(fd);
}

void	in_redirection(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		(perror("open"), exit(EXIT_FAILURE));
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		(perror("dup2"), exit(EXIT_FAILURE));
	}
	close(fd);
}

void	out_redirection(char *file)
{
	int		fd;

	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd == -1)
		(perror("open"), exit(EXIT_FAILURE));
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		(perror("dup2"), exit(EXIT_FAILURE));
	}
	close(fd);
}

void	append_out_redir(char *file)
{
	int		fd;

	fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (fd == -1)
		(perror("open"), exit(EXIT_FAILURE));
	if (dup2(fd, STDOUT_FILENO) == -1)
		(perror("dup2"), exit(EXIT_FAILURE));
	close(fd);
}

void	redirection(t_tree *tree)
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
			here_doc_redir(tree->redir[index].fd);
	}
}
