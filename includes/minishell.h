/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:39:24 by abbaraka          #+#    #+#             */
/*   Updated: 2024/07/27 00:29:06 by abadouab         ###   ########.fr       */
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

# define FAIL "cd: error retrieving current directory:getcwd: \
cannot access parent directories:No such file or directory\n"

# define TRUE 1
# define FALSE 0
# define ERROR -1

# define EOT 3

# define GREEN "\033[1;32m"
# define YELOW "\033[1;33m"
# define REDCL "\033[1;31m"
# define RESET "\033[0m"

extern int	g_catch_signals;

#endif
