/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by abbaraka          #+#    #+#             */
/*   Updated: 2024/07/23 10:48:44 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_numerical(t_minishell *ms, char **args, int len)
{
	if (!((args[1][len] >= '0' && args[1][len] <= '9')
	|| ((args[1][len] == '-' || args[1][len] == '+') && len == 0))
	|| (ft_strlen(args[1]) == 19
		&& ft_strncmp(args[1], "9223372036854775807", ft_strlen(args[1])) > 0)
	|| (ft_strlen(args[1]) == 20
		&& ft_strncmp(args[1], "-9223372036854775808", ft_strlen(args[1])) > 0))
		(syntax_err(ms, args[1], "numeric argument required", 255),
			exit(255));
}

void	ft_exit(t_minishell *ms, t_tree *tree, char **args)
{
	int	len;
	int	i;
	int	exit_status;

	(1) && (len = 0, i = 0);
	while (args[len])
		len++;
	(tree->no_print == 0) && (ft_putstr_fd("exit\n", 2), exit_status = 0);
	(1) && (exit_status = 0);
	while (len > 1 && args[1][i])
	{
		check_numerical(ms, args, i);
		i++;
	}
	if (len > 2)
		return (syntax_err(ms, "exit", "too many arguments", 1));
	else if (len == 2)
	{
		if (len == 2 && (args[1] == NULL || *args[1] == '\0'))
			(syntax_err(ms, args[1], "numeric argument required", 255),
				exit(255));
		len = 0;
		exit_status = ft_atoi(args[1]);
	}
	exit(exit_status);
}
