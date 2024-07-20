/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:45:58 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/20 14:58:00 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_here_doc(t_minishell *ms, pid_t pid, int fds[], int fd)
{
	char	*line;

	if (pid == 0)
	{
		line = get_next_line(&ms->leaks, fd);
		while (line)
		{
			line = splite_to_expand(ms, line, ERROR);
			write(fds[0], line, ft_strlen(line));
			line = get_next_line(&ms->leaks, fd);
		}
		if (close(fds[0]) == -1 || close(fds[1]) == -1)
			(ft_putstr_fd(strerror(errno), 2), exit(EXIT_FAILURE));
		exit(EXIT_SUCCESS);
	}
}

int	here_doc_expander(t_minishell *ms, int fd)
{
	pid_t	pid;
	int		fds[2];

	unlink("here_doc");
	fds[0] = open("here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	fds[1] = open("here_doc", O_RDONLY, 0644);
	if (fds[0] == -1 || fds[1] == -1)
		return (ft_putstr_fd(strerror(errno), 2), -1);
	(TRUE) && (unlink("here_doc"), pid = fork());
	if (pid == -1)
		return (perror("fork"), cleanup_handler(ms), -1);
	update_here_doc(ms, pid, fds, fd);
	waitpid(pid, NULL, 0);
	if (close(fds[0]) == -1 && close(fd) == -1)
		return (ft_putstr_fd(strerror(errno), 2), -1);
	return (fds[1]);
}
