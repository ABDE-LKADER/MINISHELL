/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by ||||||||          #+#    #+#             */
/*   Updated: 2024/07/26 19:09:13 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_more_args_in_one(t_minishell *ms, char **args)
{
	int		len;
	char	**split;

	split = split_args(&ms->leaks, args[1], " \t\n\r\f\v");
	len = 0;
	while (split[len])
		len++;
	if (len > 1)
		return (NULL);
	return (split[0]);
}

static void	check_numerical(t_minishell *ms, char **args)
{
	int		i;
	char	*str;

	str = check_more_args_in_one(ms, args);
	i = 0;
	if (!str)
		(syntax_err(ms, str, "numeric argument required", 255),
			exit(255));
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9') || ((str[i] == '-'
						|| str[i] == '+') && i == 0)) || (ft_strlen(str) == 19
				&& ft_strncmp(str, "9223372036854775807", ft_strlen(str)) > 0)
			|| (ft_strlen(str) == 20
				&& ft_strncmp(str, "-9223372036854775808", ft_strlen(str)) > 0))
			(syntax_err(ms, str, "numeric argument required", 255),
				exit(255));
		i++;
	}
}

void	ft_exit(t_minishell *ms, t_tree *tree, char **args)
{
	int		len;
	int		exit_status;

	len = 0;
	while (args[len])
		len++;
	(tree->no_print == 0) && (ft_putstr_fd("exit\n", 2), exit_status = 0);
	exit_status = 0;
	if (len > 1)
		check_numerical(ms, args);
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
