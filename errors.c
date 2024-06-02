/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:44:21 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/02 10:22:08 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_err(char *error_msg, int exit_status)
{
	(void)exit_status;
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd("\n", 2);
	// exit(exit_status);
}

int	check_par(char *s)
{
	int	i;
	int	level;

	i = 0;
	level = 0;
	while (s[i])
	{
		if (s[i] == '(')
		{
			level++;
			if (s[i + 1] == ')')
			return (1);
		}
		if (s[i] == ')')
			level--;
		i++;
	}
	if (level)
		return (1);
	return (0);
}