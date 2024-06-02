/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:44:46 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/02 11:22:13 by abbaraka         ###   ########.fr       */
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
		return (syntax_err("syntax error", 1), NULL);
	str = allocate(&ms->leaks, data.len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (s[data.i])
		copy_and_inject_spaces(&data, s, str);
	str[data.j] = '\0';
	return (str);
}

int	main(void)
{
	t_minishell		ms;
	char			*str;
	char			*injected_spaces;
	int				i;

	ft_bzero(&ms, sizeof(t_minishell));
	while (1)
	{
		str = readline("Minishell >$ ");
		if (!str)
			return (ft_printf("exit"), 0);
		if (*str)
			add_history(str);
		injected_spaces = inject_spaces(&ms, str);
		if (injected_spaces)
		{
			ms.tokens = ft_split_op(&ms.leaks, injected_spaces);
			i = 0;
			if (!ms.tokens)
				return (free(str), cleanup(&ms.leaks), 0);
			while (ms.tokens[i])
				printf("token: %s\n", ms.tokens[i++]);
			parse(&ms);
			free(str);
		}
	}
	cleanup(&ms.leaks);
	return (0);
}
