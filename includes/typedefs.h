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

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# include <stdbool.h>

typedef struct s_fds
{
	int		std_in;
	int		std_out;
}			t_fds;

typedef struct s_inject_data
{
	int		i;
	int		j;
	int		len;
	char	quotes;
}			t_inject_data;

typedef enum s_type
{
	CMD_T,
	PIPE_T,
	AND_T,
	OR_T
}			t_type;

typedef enum s_redirection
{
	IN_RED_T,
	OUT_RED_T,
	OUT_RED_APPEND_T,
	HERE_DOC_T
}			t_redirection;

typedef struct s_redir
{
	t_redirection		redirection;
	char				*redir_name;
	int					fd;
}						t_redir;

typedef struct s_tree
{
	t_type				type;
	char				*value;
	char				**args;
	int					args_index;
	bool				redir_ex;
	t_redir				*redir;
	int					dis_error;
	int					syntax_err;
	int					redir_index;
	struct s_tree		*left;
	struct s_tree		*right;
}						t_tree;

typedef struct s_environ
{
	void				*var;
	void				*val;
	struct s_environ	*next;
}						t_environ;

// This structure holds the main state
//	and configurations for the M1N15H3LL program.

typedef struct s_minishell
{
	t_tree			*tree;
	t_allocate		*leaks;
	t_allocate		*alloc;
	t_environ		*env;
	t_environ		*export;
	char			*read;
	char			**tokens;
	int				exit_status;
}					t_minishell;

#endif
