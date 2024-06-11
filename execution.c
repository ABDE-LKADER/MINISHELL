/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:54:33 by abadouab          #+#    #+#             */
/*   Updated: 2024/06/11 20:02:43 by abadouab         ###   ########.fr       */
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
	// char	*args[2];

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		redirection(tree);
		// args = expanding(ms, tree->args); // STILL NOT WORKING
		path = fetch_path(ms, ms->env, tree->value);
		if (execve(path, tree->args, env) == -1)
			(perror("Minishell"),
				exit(127));
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		ms->exit_status = g_catch_signals + 128;
	else if (WIFEXITED(status))
		ms->exit_status = WEXITSTATUS(status);
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
