/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by abbaraka          #+#    #+#             */
/*   Updated: 2024/07/24 10:23:03 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_print_options(char **args, int *i, int *option)
{
	int		j;
	int		found;

	found = 0;
	while (args[*i])
	{
		if (args[*i][0] == '-')
		{
			if (ft_strlen(args[*i]) < 2)
				return ;
			j = 1;
			while (args[*i][j])
			{
				if (args[*i][j] == 'n')
					(TRUE) && (found = 1, j++);
				else if (args[*i][j] != '\0' && args[*i][j] != 'n')
					return ;
			}
			if (found)
				*option = 1;
		}
		else
			return ;
		(*i)++;
	}
}

void	ft_echo(t_minishell *ms, char **args)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	check_print_options(args, &i, &option);
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!option)
		ft_putstr_fd("\n", 1);
	ms->exit_status = 0;
}
