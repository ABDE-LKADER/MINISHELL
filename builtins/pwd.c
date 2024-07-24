/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:57:24 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/24 10:26:15 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_minishell *ms)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
		(ft_printf("%s\n", path), ms->exit_status = 0, free(path));
	else if (ms->saved)
		(ft_printf("%s\n", ms->saved), ms->exit_status = 0);
	else if (!path)
		(perror("getcwd"), ms->exit_status = 1);
}
