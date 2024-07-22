/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:54:33 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/22 19:27:34 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_minishell *ms, t_tree *tree)
{
	int		index;

	if (!tree || g_catch_signals == SIGINT)
		return ;
	if (tree->type == PIPE_T)
	{
		pipeline_handler(ms, tree);
		return ;
	}
	execution(ms, tree->left);
	if (tree->type == CMD_T)
	{
		index = -1;
		expanding(ms, tree);
		while (tree->args[++index])
			;
		modify_env_val(ms, "_", tree->args[index - 1]);
		if (check_if_builtins(tree->value))
			built_in_execute(ms, tree);
		else
			command_execute(ms, tree);
	}
	if ((tree->type == AND_T && !ms->exit_status)
		|| (tree->type == OR_T && ms->exit_status))
		execution(ms, tree->right);
}
