/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/24 11:25:34 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	modify_pwd_val(t_minishell *ms, char *parent)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
		modify_env_val(ms, "PWD", path);
	else if (!path && !ft_strncmp(parent, ".", ft_strlen(parent)))
		modify_env_val(ms, "PWD", ft_strjoin(&ms->alloc,
				get_env_val(ms, "PWD"), "/."));
	else if (!path &&!ft_strncmp(parent, "..", ft_strlen(parent))
		&& ft_strlen("..") == ft_strlen(parent))
		modify_env_val(ms, "PWD", ft_strjoin(&ms->alloc,
				get_env_val(ms, "PWD"), "/.."));
	if (!path)
		ft_putstr_fd(FAIL, 2);
	free(path);
}

void	change_directory(t_minishell *ms, char *path)
{
	if (!path)
		return ;
	printf("|%s|\n", path);
	if (ft_strncmp(path, "-", ft_strlen(path)) == 0)
	{
		path = get_env_val(ms, "OLDPWD");
		if (!path)
			syntax_err(ms, "cd", "OLDPWD not set", 1);
		else
			printf("%s\n", path);
	}
	if (path && chdir(path) == -1)
		error_handler(ms, path);
	else if (path)
		ms->exit_status = 0;
}

void	ft_cd(t_minishell *ms, char **args)
{
	int			len;
	char		*path;

	len = 0;
	while (args[len])
		len++;
	if (len == 1)
	{
		path = get_env_val(ms, "HOME");
		if (!path)
			syntax_err(ms, *args, "HOME not set", 1);
		change_directory(ms, path);
	}
	else if (len == 2)
	{
		path = *(args + 1);
		change_directory(ms, path);
	}
	else
		syntax_err(ms, *args, "too many arguments", 1);
	if (ms->exit_status != 0)
		return ;
	(modify_env_val(ms, "OLDPWD", get_env_val(ms, "PWD")),
		modify_pwd_val(ms, path), ms->saved = get_env_val(ms, "PWD"));
}
