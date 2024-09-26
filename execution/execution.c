/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:54:33 by abadouab          #+#    #+#             */
/*   Updated: 2024/09/26 15:51:53 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_values(t_minishell *ms, t_tree *tree)
{
	int		index;

	index = -1;
	if (!tree->args || !*tree->args)
		return ;
	while (tree->args[++index])
		;
	modify_env_val(ms, "_", tree->args[index - 1]);
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
	while (paths && *paths)
	{
		*paths = ft_strjoin(&ms->leaks, *paths, "/");
		*paths = ft_strjoin(&ms->leaks, *paths, cmd);
		if (!access(*paths, X_OK))
			return (*paths);
		paths++;
	}
	return (NULL);
}

static void	command_execute(t_minishell *ms, t_tree *tree)
{
	pid_t	pid;
	char	*path;

	sig_childer();
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		if (redirection(ms, tree) == -1)
			exit(EXIT_FAILURE);
		if (!tree->value)
			exit(EXIT_SUCCESS);
		path = fetch_path(ms, ms->env, tree->value);
		if (tree->dis_error)
			exit(ms->exit_status);
		if (execve(path, tree->args, change_linked_to_double(ms)) == -1)
			execution_errors(ms, tree, path);
	}
	waitpid(pid, &ms->status, 0);
	set_signals(ms->status);
	if (WIFSIGNALED(ms->status))
		ms->exit_status = g_catch_signals + 128;
	else if (WIFEXITED(ms->status))
		ms->exit_status = WEXITSTATUS(ms->status);
}

void	execution(t_minishell *ms, t_tree *tree)
{
	int		len;

	if (!tree || g_catch_signals == SIGINT)
		return ;
	if (tree->type == PIPE_T)
		return (pipeline_handler(ms, tree));
	execution(ms, tree->left);
	if (tree->type == CMD_T)
	{
		len = 0;
		while (tree->args[len])
			len++;
		expanding(ms, tree, len);
		update_env_values(ms, tree);
		if (check_if_builtins(tree->value))
			built_in_execute(ms, tree);
		else
			command_execute(ms, tree);
		clean_fds(tree);
	}
	if ((tree->type == AND_T && !ms->exit_status)
		|| (tree->type == OR_T && ms->exit_status))
		execution(ms, tree->right);
}
