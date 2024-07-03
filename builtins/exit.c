/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: |||||||| <||||||||@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by ||||||||          #+#    #+#             */
/*   Updated: 2024/06/11 14:46:14 by ||||||||         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_minishell *ms, char **args)
{
	int	len;
	int	exit_status;

	len = 0;
	while (args[len])
		len++;
	ft_printf("exit\n");
	exit_status = 0;
	if (len > 2)
		(syntax_err(ms, "exit", "too many arguments", 1),
			exit(1));
	else if (len == 2)
	{
		len = 0;
		while (args[1][len])
		{
			if (!((args[1][len] >= '0' && args[1][len] <= '9')
				|| ((args[1][len] == '-' || args[1][len] == '+') && len == 0)))
				(syntax_err(ms, args[1], "numeric argument required", 2),
					exit(2));
			len++;
		}
		exit_status = ft_atoi(args[1]);
	}
	exit(exit_status);
}
