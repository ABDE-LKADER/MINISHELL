/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:39:24 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/03 20:27:26 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "mylib.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

int	g_sig;

typedef struct s_inject_data
{
	int		i;
	int		j;
	int		len;
	char	quotes;
}			t_inject_data;

// typedef enum	s_operator_type
// {
//     OP_AND,
//     OP_OR
// } 				operator_type_t;

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
	void				*value;
	void				**args;
	int					args_index;
	t_redir				*redir;
	int					syntax_err;
	int					redir_index;
	struct s_tree		*left;
	struct s_tree		*right;
}						t_tree;

typedef struct s_environ
{
	char				*content;
	struct s_environ	*next;
}						t_environ;

// This structure holds the main state
//	and configurations for the M1N15H3LL program.

typedef struct s_minishell
{
	t_tree			*tree;
	t_allocate		*leaks;
	t_allocate		*locked;
	t_environ		*env;
	t_environ		*export;
	char			*read;
	char			**tokens;
	int				exit_status;
}					t_minishell;

// typedef struct s_command
// {
//     void	type;
// 	char	*command;
//     void	args;
//     void	redirection;
// }				command_t;

// Inject Spaces utils

int			count_op(char *s);
int			check_sep(char c);
void		copy_and_inject_spaces(t_inject_data *data, char *s, char *str);
int			check_par(char *s);

///////////////// PROTOTYPES TOKENIZATION /////////////////

int			cmp_operators(char c);
void		tokenize_operators(char *s, int *j, char **arr, int w);
void		get_tokens(char *s, int *j, char *quotes);
int			words_counter(const char *s);
char		**ft_split_op(t_allocate **leaks, char const *s);

int			check_token_op(char *token);
void		syntax_err(t_minishell *ms, char *error_msg, int exit_status);
void		set_redir(t_minishell *ms, int *i);
int			check_if_operator(char *token);
int			check_redirection(t_minishell *ms, int *i, int *redir_set);
void		check_args(t_tree *node, char **tokens, int len);
int			check_redir_at_end(t_minishell *ms, int *i, int *redir_set);
int			check_closed_quotes(char **tokens, int i, int j);
int			check_valid_op(char *token);
void		set_op(t_tree *tree, char *token);

///////////////// HERE_DOC /////////////////

int	ft_open_here_doc(char *delimiter);

t_tree		*parse_simple_command(t_minishell *ms, int *i);
t_tree		*parse_exp(t_minishell *ms, int *i, int min_pr);
t_tree		*parse_tree(t_minishell *ms);

///////////////// SIGNAL PROTOTYPES /////////////////

void		sig_handler(void);
void		sig_heredoc(void);

///////////////// ENVIRONMENT PROTOTYPES /////////////////

void	environment_init(t_minishell *ms, char **env);

///////////////// ERROR PROTOTYPES /////////////////

void	error_handler(t_minishell *ms);

#endif
