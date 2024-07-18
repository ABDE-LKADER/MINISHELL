/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:30:49 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/18 06:36:22 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child(t_minishell *ms, t_tree *tree, int pipefd[2])
{
	char	*path;

	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (tree->type != CMD_T)
		execution(ms, tree);
	else
	{
		expanding(ms, tree);
		if (redirection(ms, tree) == -1)
			exit(EXIT_FAILURE);
		if (check_if_builtins(tree->value))
			(built_in_execute(ms, tree),exit(ms->exit_status));
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
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		(perror("pipe"), exit(1), cleanup_handler(ms));
	pid = fork();
	if (pid == -1)
		(perror("fork"), exit(1), cleanup_handler(ms));
	else if (pid == 0)
		execute_child(ms, tree, pipefd);
	else
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	execute_last(t_minishell *ms, t_tree *tree)
{
	char	*path;

	if (tree->type != CMD_T)
		(execution(ms, tree), exit(ms->exit_status));
	else
	{
		expanding(ms, tree);
		if (redirection(ms, tree) == -1)
			exit(EXIT_FAILURE);
		if (check_if_builtins(tree->value))
			(built_in_execute(ms, tree),exit(ms->exit_status));
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

void	last_command(t_minishell *ms, t_tree *tree, int *std)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid == -1)
		(perror("fork"), exit(1), cleanup_handler(ms));
	if (pid == 0)
		execute_last(ms, tree);
	else
	{
		dup2(std[0], STDIN_FILENO);
		dup2(std[1], STDOUT_FILENO);
		close(std[0]);
		close(std[1]);
		waitpid(pid, &status, 0);
		while (wait(NULL) != -1)
			;
		(WIFEXITED(status)) && (ms->exit_status = WEXITSTATUS(status));
	}
}

void	pipeline_handler(t_minishell *ms, t_tree *tree)
{
	t_tree	*tmp;
	int		std[2];

	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	tmp = tree->next;
	while (tmp)
	{
		if (tmp->next == NULL)
		{
			last_command(ms, tmp, std);
			break;
		}
		create_process(ms, tmp);
		tmp = tmp->next;
	}
	tmp = tree->next;
}
