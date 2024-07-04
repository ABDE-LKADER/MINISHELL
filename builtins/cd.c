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
	if (chdir(path) == -1)
		error_handler(ms, path);
	else
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
		change_directory(ms, *(args + 1));
	else
		syntax_err(ms, *args, "too many arguments", 1);
	if (ms->exit_status != 0)
		return ;
	modify_env_val(ms, "OLDPWD", get_env_val(ms, "PWD"));
	path = getcwd(NULL, 0);
	if (path)
		modify_env_val(ms, "PWD", path);
	else
		modify_env_val(ms, "PWD", ft_strjoin(&ms->alloc, get_env_val(ms, "PWD"), "/.."));
	free(path);
}
