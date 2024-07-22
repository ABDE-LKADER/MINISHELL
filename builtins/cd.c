/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by ||||||||          #+#    #+#             */
/*   Updated: 2024/07/22 13:09:22 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	modify_env_val(t_minishell *ms, char *env_var, char *val)
{
	t_environ	*tmp;

	tmp = ms->env;
	if (!val)
		return ;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, env_var, ft_strlen(tmp->var)) == 0)
		{
			tmp->val = ft_strdup(&ms->alloc, val);
			return ;
		}
		tmp = tmp->next;
	}
}

char	*get_env_val(t_minishell *ms, char *s)
{
	t_environ	*tmp;

	tmp = ms->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, s, ft_strlen(tmp->var)) == 0)
			return (tmp->val);
		tmp = tmp->next;
	}
	return (NULL);
}

void	change_directory(t_minishell *ms, char *path)
{
	if (!path)
		return ;
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

void	modify_pwd_val(t_minishell *ms)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		if (get_env_val(ms, "PWD") == NULL)
		{	
			environment_add(ms, &ms->env, "PWD", path);
			modify_env_val(ms, "PWD", path);
		}
		else	
			modify_env_val(ms, "PWD", path);
	}
	else
		modify_env_val(ms, "PWD", ft_strjoin(&ms->alloc,
				get_env_val(ms, "PWD"), "/.."));
	free(path);
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
		change_directory(ms, *(args + 1));
	else
		syntax_err(ms, *args, "too many arguments", 1);
	if (ms->exit_status != 0)
		return ;
	modify_env_val(ms, "OLDPWD", get_env_val(ms, "PWD"));
	modify_pwd_val(ms);
}
