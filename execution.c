/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:54:33 by abadouab          #+#    #+#             */
/*   Updated: 2024/06/07 12:32:45 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_minishell *ms, t_tree *tree, char **env)
{
	pid_t	pid;
	char	*path;

	if (!tree)
		return ;
	if (*(tree->value) != '|' && *(tree->value) != '&')
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			path = "/bin/";
			path = ft_strjoin(&ms->leaks, path, tree->value);
			printf("VALUE: %s\t\t\tADDRESS: %p\n", tree->value, &tree);
			printf("------------------ %d |", execve(path, tree->args, env));
			exit(EXIT_SUCCESS);
		}
	}
	execution(ms, tree->left, env);
	execution(ms, tree->right, env);
}
