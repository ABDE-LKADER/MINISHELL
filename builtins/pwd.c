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
