/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:30:49 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/30 17:10:42 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child(t_minishell *ms, t_tree *tree)
{
	int		len;
	char	*path;

	if (tree->type != CMD_T)
		(execution(ms, tree), exit(ms->exit_status));
	else
	{
		len = 0;
		while (tree->args[len])
			len++;
		tree->no_print = 1;
		expanding(ms, tree, len);
		if (redirection(ms, tree) == -1)
			exit(EXIT_FAILURE);
		if (check_if_builtins(tree->value))
			(built_in_execute(ms, tree), exit(ms->exit_status));
		else
		{
			if (!tree->value)
				exit(EXIT_SUCCESS);
			path = fetch_path(ms, ms->env, tree->value);
			if (execve(path, tree->args, change_linked_to_double(ms)) == -1)
				execution_errors(ms, tree, path);
		}
	}
}

int	create_process(t_minishell *ms, t_tree *tree)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), kill(0, SIGINT), -1);
	else if (pid == 0)
	{
		if (tree->next != NULL)
			dup2(pipefd[1], STDOUT_FILENO);
		(close(pipefd[1]), close(pipefd[0]));
		execute_child(ms, tree);
	}
	else
		(dup2(pipefd[0], STDIN_FILENO), close(pipefd[1]), close(pipefd[0]));
	return (true);
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
		set_signals(status);
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
	int		pid;

	pid = 0;
	sig_childer();
	tmp = tree->next;
	fds = save_fds();
	while (tmp->next)
	{
		if (pid == -1)
		{
			ms->exit_status = 1;
			sig_handler();
			break ;
		}
		pid = create_process(ms, tmp);
		(TRUE) && (ms->exit_status = 0, tmp = tmp->next);
	}
	last_command(ms, tmp, fds);
}
