#include "minishell.h"

int	ft_pwd(void)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	if (!dir)
		return (1);
	printf("%s", dir);
	printf("\n");
	return (0);
}
