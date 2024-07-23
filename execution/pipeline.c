/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:30:49 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/23 11:42:01 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child(t_minishell *ms, t_tree *tree)
{
	char	*path;

	if (tree->type != CMD_T)
		(execution(ms, tree), exit(ms->exit_status));
	else
	{
		tree->no_print = 1;
		expanding(ms, tree);
		if (redirection(ms, tree) == -1)
			exit(EXIT_FAILURE);
		if (check_if_builtins(tree->value))
			(built_in_execute(ms, tree), exit(ms->exit_status));
		else
		{
			if (!tree->value || !*tree->value)
				exit(EXIT_SUCCESS);
			path = fetch_path(ms, ms->env, tree->value);
			if (execve(path, tree->args, change_linked_to_double(ms)) == -1)
				execution_errors(ms, tree, path);
		}
	}
}

void	create_process(t_minishell *ms, t_tree *tree)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		(perror("fork"), kill(0, SIGINT), g_catch_signals = 2);
	else if (pid == 0)
	{
		if (tree->next != NULL)
			dup2(pipefd[1], STDOUT_FILENO);
		(close(pipefd[1]), close(pipefd[0]));
		execute_child(ms, tree);
	}
	else
		(dup2(pipefd[0], STDIN_FILENO), close(pipefd[1]), close(pipefd[0]));
}

void	last_command(t_minishell *ms, t_tree *tree, t_fds fds)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid == -1)
		(perror("fork"));
	if (pid == 0)
		execute_child(ms, tree);
	else
	{
		restore_fds(fds);
		waitpid(pid, &status, 0);
		while (wait(NULL) != -1)
			;
		if (ms->exit_status == 1)
			return ;
		if (WIFSIGNALED(status))
			ms->exit_status = g_catch_signals + 128;
		else if (WIFEXITED(status))
			ms->exit_status = WEXITSTATUS(status);
	}
}

void	pipeline_handler(t_minishell *ms, t_tree *tree)
{
	t_tree	*tmp;
	t_fds	fds;

	fds = save_fds();
	tmp = tree->next;
	while (tmp->next)
	{
		if (g_catch_signals == 2)
		{
			ms->exit_status = 1;
			break ;
		}
		create_process(ms, tmp);
		tmp = tmp->next;
	}
	last_command(ms, tmp, fds);
}
