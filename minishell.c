/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:44:46 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/04 18:29:53 by abadouab         ###   ########.fr       */
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
		return (syntax_err(ms, "syntax error", 258), NULL);
	str = allocate(&ms->leaks, data.len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (s[data.i])
		copy_and_inject_spaces(&data, s, str);
	str[data.j] = '\0';
	return (str);
}

void	parser(t_minishell *ms)
{
	char			*injected_spaces;
	int				i;

	if (*ms->read)
		add_history(ms->read);
	injected_spaces = inject_spaces(ms, ms->read);
	if (!injected_spaces)
		error_handler(ms);
	ms->tokens = ft_split_op(&ms->leaks, injected_spaces);
	if (!ms->tokens)
		error_handler(ms);
	i = 0;
	while (ms->tokens[i])
		printf("token: %s\n", ms->tokens[i++]);
	parse_tree(ms);
}

int	main(int ac, char **av, char **env)
{
	t_minishell		ms;

	(void)ac;
	(void)av;
	sig_handler();
	environment_init(&ms, env);
	while (1)
	{
		g_sig = 0;
		ms.read = readline("Minishell >$ ");
		if (!ms.read)
			return (printf(EXIT), EXIT_SUCCESS);
		while (ms.export)
		{
			printf("\n --------------------------------------------------------\n VAR: %s || \n--------------------------------------------------------\n VAL: %s ||", ms.export->var, ms.export->val);
			ms.export = ms.export->next;
		}
		parser(&ms);
		(cleanup(&ms.leaks), free(ms.read));
		// if (ms.exit_status == 1)
		// 	continue;
	}
	return (cleanup(&ms.leaks), EXIT_SUCCESS);
}
