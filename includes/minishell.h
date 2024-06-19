/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darkab <darkab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:39:24 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/13 20:14:16 by darkab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "mylib.h"
# include "prototypes.h"
# include <stdio.h>
// # include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
#include <sys/errno.h>

# define EXIT "\033[AMinishell >$ exit\n"
# define INIT "\033[A\n>   \n"
# define TRUE 1
# define FALSE 0

# define GREEN "\033[1;32m"
# define YELOW "\033[1;33m"
# define REDCL "\033[1;31m"
# define RESET "\033[0m"

extern int	g_catch_signals;

#endif
