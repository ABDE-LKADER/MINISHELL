#include "minishell.h"

char	*find_last_backslash(char *s)
{
	int	i;
	int	last_slash;

	i = 0;
	last_slash = 0;
	while (s[i])
	{
		if (s[i] == '/')
			last_slash = i;
		i++;
	}
	if (last_slash == 0)
		s[last_slash + 1] = '\0';
	else
		s[last_slash] = '\0';
	return (s);
}

char	*get_env_val(t_minishell *ms, char *s)
{
	t_environ	*tmp;

	tmp = ms->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, s, ft_strlen(tmp)) == 0)
			return (tmp->val);
		tmp = tmp->next;
	}
}

void	ft_cd(t_minishell *ms, char **args)
{
	int			len;
	const char	*path;
	DIR			*dir;

	len = 0;
	while (args[len])
		len++;
	if (len == 1)
	{
		path = get_env_val(ms, "HOME");
		if (path)
			if (chdir(path) == -1)
				syntax_err(ms, path, "No such file or directory", 1);
	}
	else if (len == 2)
	{
		path = args[1];
		if (ft_strncmp(path, "..", ft_strlen(path)) == 0)
			(1) && (path = get_env_val(ms, "PWD"),
			path = find_last_backslash(path));
		if (chdir(path) == -1)
			syntax_err(ms, path, "No such file or directory", 1);
	}
	else
		syntax_err(ms, *args, "too many arguments", 1);
}
