/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:54:33 by abadouab          #+#    #+#             */
/*   Updated: 2024/06/08 02:43:26 by abadouab         ###   ########.fr       */
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
		printf("PATH: %s\n", *paths);
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

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		path = fetch_path(ms, ms->env, tree->value);
		if (!path)
			return ;
		if (execve(path, tree->args, env) == -1)
			(syntax_err(ms, "command not found\n", 127),
				exit(EXIT_FAILURE));
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
}

void	execution(t_minishell *ms, t_tree *tree, char **env)
{

	if (!tree)
		return ;
	printf("THE PLACE YOU ARE : %s\n", tree->value);
	execution(ms, tree->left, env);
	if (*(tree->value) != '|' && *(tree->value) != '&')
		command_execute(ms, tree, env);
	printf("THE PLACE YOU ARE : %s\n", tree->value);
	if (!ft_strncmp(tree->value, "&&", ft_strlen("&&")))
		execution(ms, tree->right, env);
}
