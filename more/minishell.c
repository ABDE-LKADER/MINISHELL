/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:44:46 by abbaraka          #+#    #+#             */
/*   Updated: 2024/07/18 11:48:05 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_minishell *ms)
{
	char	*injected_spaces;

	if (*ms->prompt)
		add_history(ms->prompt);
	injected_spaces = inject_spaces(ms, ms->prompt);
	if (!injected_spaces)
		return ;
	ms->tokens = ft_split_op(&ms->leaks, injected_spaces);
	if (!ms->tokens)
		cleanup_handler(ms);
	if (check_ops_and_cmds(ms) == -1)
		return ;
	if (parse_tree(ms) == NULL)
		ms->tree = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_minishell		ms;

	(sig_handler(), environment_init(&ms, env, ac, av));
	while (1)
	{
		(TRUE) && (g_catch_signals = 0, ms.tree = NULL,
		ms.prompt = readline("Minishell >$ "));
		if (!ms.prompt)
			return (ft_printf(EXIT), clear_history(),
				cleanup(&ms.leaks), cleanup(&ms.alloc), ms.exit_status);
		(g_catch_signals == SIGINT) && (ms.exit_status = 1,
			g_catch_signals = 0);
		if (!(*ms.prompt))
		{
			(free(ms.prompt));
			continue ;
		}
		(parser(&ms), execution(&ms, ms.tree),
			cleanup(&ms.leaks), free(ms.prompt));
	}
	return (clear_history(), cleanup(&ms.leaks),
		cleanup(&ms.alloc), EXIT_SUCCESS);
}
