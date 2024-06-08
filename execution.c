/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:54:33 by abadouab          #+#    #+#             */
/*   Updated: 2024/06/08 16:59:48 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fetch_path(t_minishell *ms, t_environ *env, char *cmd)
{
	char	**paths;

	while (env && ft_strncmp("PATH", env->var, ft_strlen("PATH")))
		env = env->next;
	paths = ft_split(&ms->leaks, env->val, ':');
	while (*paths)
	{
		*paths = ft_strjoin(&ms->alloc, *paths, "/");
		*paths = ft_strjoin(&ms->alloc, *paths, cmd);
		if (!access(*paths, X_OK))
			return (*paths);
		paths++;
	}
	return (NULL);
}

void	command_execute(t_minishell *ms, t_tree *tree, char **env)
{
	pid_t	pid;
	char	*path;
	int		status;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		path = fetch_path(ms, ms->env, tree->value);
		if (execve(path, tree->args, env) == -1)
			(syntax_err(ms, "command not found", 127),
				exit(127));
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ms->exit_status = WEXITSTATUS(status);
}

void	exec_child_pipe(t_minishell *ms, t_tree *tree, int fds[2], char **env, int set)
{
	if (set == 1)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		close(fds[0]);
	}
	else if (set == 0)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[1]);
		close(fds[0]);
	}
	execution(ms, tree, env);
	exit(ms->exit_status);
	
}

int	pipeline_handler(t_minishell *ms, t_tree *tree, char **env)
{
	int		fds[2];
	pid_t	f_pid;
	pid_t	s_pid;
	int		status;

	if (pipe(fds) == -1)
		return (perror("pipe"), error_handler(ms), 1);
	f_pid = fork();
	if (f_pid == -1)
		return (perror("fork"), error_handler(ms), 1);
	if (f_pid == 0)
		exec_child_pipe(ms, tree->left, fds, env, 1);
	s_pid = fork();
	if (s_pid == -1)
		return (perror("fork"), error_handler(ms), 1);
	if (s_pid == 0)
		exec_child_pipe(ms, tree->right, fds, env, 0);
	close(fds[1]);
	close(fds[0]);
	waitpid(f_pid, &status, 0);
	waitpid(s_pid, &status, 0);
	if (WIFEXITED(status))
		ms->exit_status = WEXITSTATUS(status);
	return (1);
}

void	execution(t_minishell *ms, t_tree *tree, char **env)
{
	if (!tree)
		return ;
	if (tree->type == PIPE_T)
	{
		pipeline_handler(ms, tree, env);
		return ;
	}
	execution(ms, tree->left, env);
	if (tree->type == CMD_T)
		command_execute(ms, tree, env);
	if ((tree->type == AND_T && !ms->exit_status)
		|| (tree->type == OR_T && ms->exit_status))
		execution(ms, tree->right, env);
}
