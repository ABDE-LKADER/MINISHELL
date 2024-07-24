/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:39:24 by abbaraka          #+#    #+#             */
/*   Updated: 2024/07/24 12:51:12 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "mylib.h"
# include "prototypes.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <sys/errno.h>

# define EXIT "\033[AMinishell >$ exit\n"
# define INIT "\033[A\n>   \n"
# define AMBG "ambiguous redirect"

# define FAIL1 "cd: error retrieving current directory:"
# define FAIL2 "getcwd: cannot access parent directories:"
# define FAIL3 "No such file or directory\n"
#define FAIL FAIL1 FAIL2 FAIL3

# define TRUE 1
# define FALSE 0
# define ERROR -1

# define EOT 3

# define GREEN "\033[1;32m"
# define YELOW "\033[1;33m"
# define REDCL "\033[1;31m"
# define RESET "\033[0m"

int	g_catch_signals;

#endif
