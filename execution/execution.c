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

void	execution(t_minishell *ms, t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->type == PIPE_T)
	{
		pipeline_handler(ms, tree);
		return ;
	}
	execution(ms, tree->left);
	if (tree->type == CMD_T)
	{
		expanding(ms, tree);
		if (check_if_builtins(tree->value))
			built_in_execute(ms, tree);
		else
			command_execute(ms, tree);
	}
	if ((tree->type == AND_T && !ms->exit_status)
		|| (tree->type == OR_T && ms->exit_status))
		execution(ms, tree->right);
}
