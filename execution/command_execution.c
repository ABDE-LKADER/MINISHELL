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

	if (!cmd)
		return (NULL);
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
		*paths = ft_strjoin(&ms->leaks, *paths, "/");
		*paths = ft_strjoin(&ms->leaks, *paths, cmd);
		if (!access(*paths, X_OK))
			return (*paths);
		paths++;
	}
	return (NULL);
}

char	**change_linked_to_double(t_minishell *ms)
{
	t_environ	*tmp;
	int			len;
	char		**env;
	int			i;

	tmp = ms->env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	env = allocate(&ms->alloc, len, sizeof(char *));
	tmp = ms->env;
	i = 0;
	while (tmp)
	{
		env[i] = ft_strjoin(ms->alloc, tmp->var, "=");
		env[i] = ft_strjoin(ms->alloc, env[i], tmp->val);
		i++;
		tmp = tmp->next;
	}
	return (env);
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
		expanding(ms, tree);
		if (!tree->value || !*tree->value)
			exit(EXIT_SUCCESS);
		path = fetch_path(ms, ms->env, tree->value);
		env = change_linked_to_double(ms);
		if (execve(path, tree->args, env) == -1)
			execution_errors(ms, tree, path);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		ms->exit_status = g_catch_signals + 128;
	else if (WIFEXITED(status))
		ms->exit_status = WEXITSTATUS(status);
}
