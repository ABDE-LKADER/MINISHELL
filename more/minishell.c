/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darkab <darkab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:44:46 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/13 20:13:52 by darkab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_catch_signals = 0;

void	parser(t_minishell *ms)
{
	char	*injected_spaces;

	ms->exit_status = 0;
	if (*ms->read)
		add_history(ms->read);
	injected_spaces = inject_spaces(ms, ms->read);
	if (!injected_spaces)
		return ;
	ms->tokens = ft_split_op(&ms->leaks, injected_spaces);
	if (!ms->tokens)
		error_handler(ms);
	if (check_ops_and_cmds(ms) == -1)
		return ;
	parse_tree(ms);
}

int	main(int ac, char **av, char **env)
{
	t_minishell		ms;

	(sig_handler(), environment_init(&ms, env, ac, av));
	while (1)
	{
		(TRUE) && (g_catch_signals = 0, ms.tree = NULL,
		ms.read = readline("Minishell >$ "));
		if (!ms.read)
			return (printf(EXIT), cleanup(&ms.leaks),
				cleanup(&ms.alloc), EXIT_SUCCESS);
		(g_catch_signals == SIGINT) && (ms.exit_status = 1);
		if (!(*ms.read))
		{
			free(ms.read);
			continue ;
		}
		(parser(&ms), execution(&ms, ms.tree, env),
			cleanup(&ms.leaks), free(ms.read));
		printf("EXIT STATUS : %d\n", ms.exit_status);
	}
	return (cleanup(&ms.leaks), cleanup(&ms.alloc), EXIT_SUCCESS);
}
