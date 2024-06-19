#include "minishell.h"

void change_directory(const char* path) {
    if (chdir(path) == -1) {
        perror("chdir");
    } else {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Changed directory to: %s\n", cwd);
        } else {
            perror("getcwd");
        }
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
