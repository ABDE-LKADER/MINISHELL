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

void	ft_pwd(t_minishell *ms)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("getcwd");
		ms->exit_status = 1;
		return ;
	}
	ft_printf("%s", path);
	ft_printf("\n");
	free(path);
	ms->exit_status = 0;
}
