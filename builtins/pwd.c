/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:57:24 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/25 06:45:26 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_minishell *ms)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
		return (ft_printf("%s\n", path), ms->exit_status = 0, free(path));
	else if (ms->saved)
		return (ms->exit_status = 0, (void)ft_printf("%s\n", ms->saved));
	else if (!path)
		return (ms->exit_status = 1, perror("getcwd"));
}
