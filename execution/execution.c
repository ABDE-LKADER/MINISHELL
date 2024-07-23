/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:54:33 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/23 10:49:47 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_fds(t_tree *tree)
{
	int		index;

	index = -1;
	while (++index < tree->redir_index)
	{
		if (tree->redir[index].fd != -1)
			close(tree->redir[index].fd);
	}
}

void	update_env_values(t_minishell *ms, char **args)
{
	int		index;

	index = -1;
	if (!args || !*args)
		return ;
	while (args[++index])
		;
	modify_env_val(ms, "_", args[index - 1]);
}

void	execution(t_minishell *ms, t_tree *tree)
{
	if (!tree || g_catch_signals == SIGINT)
		return ;
	if (tree->type == PIPE_T)
		return (pipeline_handler(ms, tree));
	execution(ms, tree->left);
	if (tree->type == CMD_T)
	{
		expanding(ms, tree);
		update_env_values(ms, tree->args);
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
