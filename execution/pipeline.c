/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:30:49 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/20 09:20:44 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	first_child_exec(t_minishell *ms, t_tree *tree, int fds[2])
// {
// 	dup2(fds[1], STDOUT_FILENO);
// 	close(fds[1]);
// 	close(fds[0]);
// 	execution(ms, tree);
// 	exit(ms->exit_status);
// }

// void	second_child_exec(t_minishell *ms, t_tree *tree, int fds[2])
// {
// 	dup2(fds[0], STDIN_FILENO);
// 	close(fds[1]);
// 	close(fds[0]);
// 	execution(ms, tree);
// 	exit(ms->exit_status);
// }

// void	pipeline_handler(t_minishell *ms, t_tree *tree)
// {
// 	int		fds[2];
// 	pid_t	f_pid;
// 	pid_t	s_pid;
// 	int		status;

// 	if (pipe(fds) == -1)
// 		(perror("pipe"), cleanup_handler(ms));
// 	f_pid = fork();
// 	if (f_pid == -1)
// 		(perror("fork"), cleanup_handler(ms));
// 	if (f_pid == 0)
// 		first_child_exec(ms, tree->left, fds);
// 	s_pid = fork();
// 	if (s_pid == -1)
// 		(perror("fork"), cleanup_handler(ms));
// 	if (s_pid == 0)
// 		second_child_exec(ms, tree->right, fds);
// 	(TRUE) && (close(fds[1]), close(fds[0]));
// 	(TRUE) && (waitpid(s_pid, &status, 0), waitpid(f_pid, NULL, 0));
// 	(WIFEXITED(status)) && (ms->exit_status = WEXITSTATUS(status));
// }

void	execute_child(t_minishell *ms, t_tree *tree)
{
	char	*path;


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

int	find_redir_type(t_tree *tmp, t_redirection type)
{
	int	i;

	i = 0;
	while (i < tmp->redir_index)
	{
		if (tmp->redir[i].redirection == type)
			return (1);
		i++;
	}
	return (0);
}

int	create_process(t_minishell *ms, t_tree *tree)
{
	pid_t pid;
	int pipefd[2];

	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	else if ((pid = fork()) == -1)
		(perror("fork"), kill(0, SIGINT), g_catch_signals = 2);
	else if (pid == 0)
	{
		if (tree->next != NULL)
			dup2(pipefd[1], STDOUT_FILENO);
		(close(pipefd[1]), close(pipefd[0]));
		execute_child(ms, tree, pipefd);
	}
	else
		(dup2(pipefd[0], STDIN_FILENO), close(pipefd[1]), close(pipefd[0]));
	return (FALSE);
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
		(perror("fork"));
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
	int		pid;

	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	tmp = tree->next;
	while (tmp->next)
	{
		if (tmp->next == NULL)
			last_command(ms, tmp, std);
		if (g_catch_signals == 2)
			break ;
		pid = create_process(ms, tmp);
		tmp = tmp->next;
	}
}
