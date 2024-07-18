/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/18 06:47:04 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_builtins(char *cmd)
{
	if (!cmd)
		return (FALSE);
	if ((!ft_strncmp(cmd, "echo", ft_strlen(cmd))
			&& ft_strlen(cmd) == ft_strlen("echo"))
		|| (!ft_strncmp(cmd, "cd", ft_strlen(cmd))
			&& ft_strlen(cmd) == ft_strlen("cd"))
		|| (!ft_strncmp(cmd, "pwd", ft_strlen(cmd))
			&& ft_strlen(cmd) == ft_strlen("pwd"))
		|| (!ft_strncmp(cmd, "export", ft_strlen(cmd))
			&& ft_strlen(cmd) == ft_strlen("export"))
		|| (!ft_strncmp(cmd, "unset", ft_strlen(cmd))
			&& ft_strlen(cmd) == ft_strlen("unset"))
		|| (!ft_strncmp(cmd, "env", ft_strlen(cmd))
			&& ft_strlen(cmd) == ft_strlen("env"))
		|| (!ft_strncmp(cmd, "exit", ft_strlen(cmd))
			&& ft_strlen(cmd) == ft_strlen("exit")))
		return (TRUE);
	return (FALSE);
}

void	built_in_execute(t_minishell *ms, t_tree *tree)
{
	t_fds	fds;

	fds = save_fds();
	if (redirection(ms, tree) == -1)
		return ;
	if (!ft_strncmp(*tree->args, "echo", ft_strlen(*tree->args)))
		ft_echo(ms, tree->args);
	else if (!ft_strncmp(*tree->args, "cd", ft_strlen(*tree->args)))
		ft_cd(ms, tree->args);
	else if (!ft_strncmp(*tree->args, "pwd", ft_strlen(*tree->args)))
		ft_pwd(ms);
	else if (!ft_strncmp(*tree->args, "export", ft_strlen(*tree->args)))
		ft_export(ms, ms->env, tree->args);
	else if (!ft_strncmp(*tree->args, "unset", ft_strlen(*tree->args)))
		ft_unset(ms, tree->args);
	else if (!ft_strncmp(*tree->args, "env", ft_strlen(*tree->args)))
		ft_env(ms, ms->env);
	else if (!ft_strncmp(*tree->args, "exit", ft_strlen(*tree->args)))
		ft_exit(ms, tree->args);
	restore_fds(fds);
}
