/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:44:21 by abbaraka          #+#    #+#             */
/*   Updated: 2024/07/24 10:13:29 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_handler(t_minishell *ms)
{
	clear_history();
	free(ms->prompt);
	cleanup(&ms->leaks);
	cleanup(&ms->alloc);
	exit(EXIT_FAILURE);
}

void	error_handler(t_minishell *ms, char *path)
{
	if (errno == ENOENT)
		syntax_err(ms, path, "No such file or directory", 1);
	else if (errno == EACCES)
		syntax_err(ms, path, "Permission denied", 1);
	else if (errno == EISDIR)
		syntax_err(ms, path, "Is a directory", 1);
	else if (errno == ENOTDIR)
		syntax_err(ms, path, "Not a directory", 1);
	else
		perror("Minishell");
}

void	execution_errors(t_minishell *ms, t_tree *tree, char *path)
{
	DIR		*dir;

	if (errno == ENOENT && *tree->value)
		(syntax_err(ms, path, "No such file or directory", 127), exit(127));
	if (errno == EACCES && *tree->value)
	{
		dir = opendir(path);
		if (dir && !closedir(dir))
			(syntax_err(ms, path, "Is a directory", 126), exit(126));
		else
			(syntax_err(ms, path, "Permission denied", 126), exit(126));
	}
	(syntax_err(ms, tree->value, "command not found", 127), exit(127));
}

void	syntax_err(t_minishell *ms, char *option, char *error_msg,
		int exit_status)
{
	if (g_catch_signals != SIGINT)
	{
		if (ms->tree && !ms->tree->dis_error)
		{
			ft_putstr_fd("Minishell: ", 2);
			if (option)
			{
				ft_putstr_fd(option, 2);
				ft_putstr_fd(": ", 2);
			}
			ft_putstr_fd(error_msg, 2);
			ft_putstr_fd("\n", 2);
		}
		else if (!ms->tree)
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(error_msg, 2);
		}
		ms->exit_status = exit_status;
		if (ms->tree)
			ms->tree->dis_error = 1;
	}
}
