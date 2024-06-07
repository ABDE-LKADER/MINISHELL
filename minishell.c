/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:44:46 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/07 22:17:08 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*inject_spaces(t_minishell *ms, char *s)
{
	char			*str;
	t_inject_data	data;

	if (!s)
		return (NULL);
	(TRUE) && (data.len = ft_strlen(s), data.len += count_op(s),
		data.i = 0, data.j = 0, data.quotes = -1);
	if (check_par(s))
		return (syntax_err(ms, "syntax error: unexpected end of file\n"
				, 258), NULL);
	str = allocate(&ms->leaks, data.len + 1, sizeof(char));
	if (!str)
		error_handler(ms);
	while (s[data.i])
		copy_and_inject_spaces(&data, s, str);
	str[data.j] = '\0';
	return (str);
}

int	check_level_par(char *input)
{
	int level;
	int cmd;
	int op;
	int	i;

	(1) && (level = 0, cmd = 0, i = -1, op = 0);
	while (input[++i])
	{
		if (input[i] == '(')
			level++;
		else if (input[i] != '&' && input[i] != '|'
			&& input[i] != ')' && input[i] != '(')
		{
			cmd++;
			while (input[i] && input[i] != '&' && input[i] != '|'
				&& input[i] != ')' && input[i] != '(')
				i++;
		}
		else if (input[i] == '&' || input[i] == '|')
		{
			op++;
			while (input[i] && input[i] != '&' && input[i] != '|')
				i++;
		}
	}
	if (level == cmd)
		return (cmd);
	return (0);
}

void	parser(t_minishell *ms)
{
	char			*injected_spaces;

	ms->exit_status = 0;
	if (*ms->read)
		add_history(ms->read);
	injected_spaces = inject_spaces(ms, ms->read);
	printf("par %d\n", check_level_par(injected_spaces));
	if (!injected_spaces)
		return ;
	ms->tokens = ft_split_op(&ms->leaks, injected_spaces);
	if (!ms->tokens)
		error_handler(ms);
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
