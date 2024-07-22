/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:39:24 by abbaraka          #+#    #+#             */
/*   Updated: 2024/07/22 10:30:32 by abadouab         ###   ########.fr       */
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

typedef struct s_expand
{
	char				*value;
	struct s_expand		*next;
}						t_expand;

typedef struct s_environ
{
	char				*var;
	char				*val;
	struct s_environ	*next;
}						t_environ;

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
	bool				set_expand;
	char				*ambig_var;
	bool				ambiguous;
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
	int					redir_err;
	int					dis_error;
	int					syntax_err;
	int					redir_index;
	int					no_print;
	struct s_tree		*left;
	struct s_tree		*right;
	struct s_tree		*next;
}						t_tree;

// This structure holds the main state
//	and configurations for the M1N15H3LL program.

typedef struct s_minishell
{
	t_tree			*tree;
	t_allocate		*leaks;
	t_allocate		*alloc;
	t_environ		*env;
	char			*prompt;
	char			**tokens;
	int				*current;
	char			**to_check;
	int				exit_status;
}					t_minishell;

#endif
