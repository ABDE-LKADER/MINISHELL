/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:57:24 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/23 09:57:28 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_minishell *ms)
{
	char	*path;
	int		cwd_null;

	(1) && (path = getcwd(NULL, 0), cwd_null = 0);
	if (!path)
	{
		(1) && (path = get_env_val(ms, "PWD"), cwd_null = 1);
		if (path)
		{
			path = ft_strdup(&ms->alloc, get_env_val(ms, "PWD"));
			if (!path)
			{
				perror("getcwd");
				ms->exit_status = 1;
				return ;
			}
		}
	}
	ft_printf("%s", path);
	ft_printf("\n");
	if (!cwd_null)
		free(path);
	ms->exit_status = 0;
}
