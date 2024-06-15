/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darkab <darkab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:54:33 by abadouab          #+#    #+#             */
/*   Updated: 2024/06/13 20:15:03 by darkab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fetch_path(t_minishell *ms, t_environ *env, char *cmd)
{
	char	**paths;

	if (!access(cmd, X_OK) && !ft_strncmp("./", cmd, ft_strlen("./")))
		return (cmd);
	if (!access(cmd, X_OK) && !ft_strncmp("/", cmd, ft_strlen("/")))
		return (cmd);
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
		redirection(tree);
		// args = expanding(ms, tree->args); // STILL NOT WORKING
		path = fetch_path(ms, ms->env, tree->value);
		if (check_if_builtins(ms, tree->args))
			exit(EXIT_SUCCESS);
		if (execve(path, tree->args, env) == -1)
			execution_errors(ms, path);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		ms->exit_status = g_catch_signals + 128;
	else if (WIFEXITED(status))
		ms->exit_status = WEXITSTATUS(status);
	if (!ft_strncmp(tree->value, "exit", ft_strlen("exit")))
		exit(ms->exit_status);
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
