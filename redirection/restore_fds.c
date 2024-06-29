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
