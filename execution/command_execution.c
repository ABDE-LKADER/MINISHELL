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

	if (!ft_strncmp("./", cmd, ft_strlen("./"))
		|| !ft_strncmp("/", cmd, ft_strlen("/")))
		return (cmd);
	while (env && ft_strncmp("PATH", env->var, ft_strlen("PATH")))
		env = env->next;
	if (!env)
		(syntax_err(ms, cmd, "No such file or directory", 127), exit(127));
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
		if (execve(path, tree->args, env) == -1)
			execution_errors(ms, path);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		ms->exit_status = g_catch_signals + 128;
	else if (WIFEXITED(status))
		ms->exit_status = WEXITSTATUS(status);
}
