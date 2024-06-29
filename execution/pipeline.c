/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:30:49 by abadouab          #+#    #+#             */
/*   Updated: 2024/06/11 20:14:18 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_child_exec(t_minishell *ms, t_tree *tree, int fds[2])
{
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	close(fds[0]);
	execution(ms, tree);
	exit(ms->exit_status);
}

void	second_child_exec(t_minishell *ms, t_tree *tree, int fds[2])
{
	dup2(fds[0], STDIN_FILENO);
	close(fds[1]);
	close(fds[0]);
	execution(ms, tree);
	exit(ms->exit_status);
}

void	pipeline_handler(t_minishell *ms, t_tree *tree)
{
	int		fds[2];
	pid_t	f_pid;
	pid_t	s_pid;
	int		status;

	if (pipe(fds) == -1)
		(perror("pipe"), error_handler(ms));
	f_pid = fork();
	if (f_pid == -1)
		(perror("fork"), error_handler(ms));
	if (f_pid == 0)
		first_child_exec(ms, tree->left, fds);
	s_pid = fork();
	if (s_pid == -1)
		(perror("fork"), error_handler(ms));
	if (s_pid == 0)
		second_child_exec(ms, tree->right, fds);
	close(fds[1]);
	close(fds[0]);
	waitpid(f_pid, &status, 0);
	waitpid(s_pid, &status, 0);
	if (WIFEXITED(status))
		ms->exit_status = WEXITSTATUS(status);
}
