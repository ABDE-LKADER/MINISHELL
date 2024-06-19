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
	printf("%s", path);
	printf("\n");
}
