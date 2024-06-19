#include "minishell.h"

void	ft_cd(t_minishell *ms, char **args)
{
	int			len;
	const char	*path;
	DIR			*dir;

	len = 0;
	while (args[len])
		len++;
	if (len == 1)
		;
	else if (len == 2)
	{
		path = args[1];
		if (chdir(path) == -1)
			syntax_err(ms, path, "No such file or directory", 1);
	}
	else
		syntax_err(ms, *args, "too many arguments", 1);
}
