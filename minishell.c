/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:44:46 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/08 02:44:28 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (ac != 1 && av)
		return (ft_putendl_fd("./minishell <empty>", 2),
			EXIT_FAILURE);
	(sig_handler(), environment_init(&ms, env));
	while (1)
	{
		(TRUE) && (g_catch_signals = 0, ms.tree = NULL,
		ms.read = readline("Minishell >$ "));
		if (!ms.read)
			return (printf(EXIT), cleanup(&ms.leaks),
				cleanup(&ms.alloc), EXIT_SUCCESS);
		printf("DEF VAL EXIT STATUS: %d\n", ms.exit_status);
		if (!(*ms.read))
			continue ;
		parser(&ms);
		printf("THE EXIT STATUS AFTER THE PARCE: %d\n", ms.exit_status);
		if (ms.exit_status != 0)
			continue ;
		(execution(&ms, ms.tree, env), cleanup(&ms.leaks), free(ms.read));
	}
	return (cleanup(&ms.leaks), cleanup(&ms.alloc), EXIT_SUCCESS);
}
