/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by ||||||||          #+#    #+#             */
/*   Updated: 2024/07/21 11:28:55 by abbaraka         ###   ########.fr       */
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

void	ft_exit(t_minishell *ms, char **args)
{
	int	len;
	int	i;
	int	exit_status;

	(1) && (len = 0, i = 0);
	while (args[len])
		len++;
	(1) && (ft_printf("exit\n"), exit_status = 0);
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
			(syntax_err(ms, args[1], "numeric argument required", 255)
			, exit(255));
		len = 0;
		exit_status = ft_atoi(args[1]);
	}
	exit(exit_status);
}
