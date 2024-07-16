/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:45:58 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/16 03:33:58 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fds	save_fds(t_fds fds)
{
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
