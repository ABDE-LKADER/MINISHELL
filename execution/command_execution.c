/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:54:33 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/16 02:37:32 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**change_linked_to_double(t_minishell *ms)
{
	int			i;
	int			len;
	t_environ	*tmp;
	char		**env;

	(1) && (tmp = ms->env, len = 0);
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	env = allocate(&ms->leaks, len + 1, sizeof(char *));
	tmp = ms->env;
	i = 0;
	while (tmp)
	{
		env[i] = ft_strjoin(&ms->leaks, tmp->var, "=");
		env[i] = ft_strjoin(&ms->leaks, env[i], tmp->val);
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

char	*fetch_path(t_minishell *ms, t_environ *env, char *cmd)
{
	DIR		*dir;
	char	**paths;

	if (!cmd)
		return (NULL);
	dir = opendir(cmd);
	if ((dir && !closedir(dir) && ft_strchr(cmd, '/'))
		|| !ft_strncmp("./", cmd, ft_strlen("./"))
		|| !ft_strncmp("/", cmd, ft_strlen("/")))
		return (cmd);
	while (env && ft_strncmp("PATH", env->var, ft_strlen("PATH")))
		env = env->next;
	if (!env || !env->val || !*env->val)
		(syntax_err(ms, cmd, "No such file or directory", 127), exit(127));
	paths = ft_split(&ms->leaks, env->val, ':');
	while (*paths)
	{
		*paths = ft_strjoin(&ms->leaks, *paths, "/");
		*paths = ft_strjoin(&ms->leaks, *paths, cmd);
		if (!access(*paths, X_OK))
			return (*paths);
		paths++;
	}
	return (NULL);
}

void	command_execute(t_minishell *ms, t_tree *tree)
{
	pid_t	pid;
	char	*path;
	int		status;

	pid = fork();
	if (pid == -1)
		(perror("fork"));
	if (pid == 0)
	{
		if (redirection(ms, tree) == -1)
			exit(EXIT_FAILURE);
		if (!tree->value || !*tree->value)
			exit(EXIT_SUCCESS);
		path = fetch_path(ms, ms->env, tree->value);
		if (tree->dis_error)
			exit(ms->exit_status);
		if (execve(path, tree->args, change_linked_to_double(ms)) == -1)
			execution_errors(ms, tree, path);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		ms->exit_status = g_catch_signals + 128;
	else if (WIFEXITED(status))
		ms->exit_status = WEXITSTATUS(status);
}
