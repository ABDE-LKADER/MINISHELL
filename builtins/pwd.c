#include "minishell.h"

void	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("getcwd");
		return ;
	}
	ft_printf("%s", path);
	ft_printf("\n");
	free(path);
}
