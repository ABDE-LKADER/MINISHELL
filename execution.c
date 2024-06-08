/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:54:33 by abadouab          #+#    #+#             */
/*   Updated: 2024/06/08 03:17:24 by abadouab         ###   ########.fr       */
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

void	execution(t_minishell *ms, t_tree *tree, char **env)
{
	if (!tree)
		return ;
	execution(ms, tree->left, env);
	if (*(tree->value) != '|' && *(tree->value) != '&')
		command_execute(ms, tree, env);
	if ((!ft_strncmp(tree->value, "&&", ft_strlen("&&")) && !ms->exit_status)
		|| (!ft_strncmp(tree->value, "||", ft_strlen("||")) && ms->exit_status))
		execution(ms, tree->right, env);
}
