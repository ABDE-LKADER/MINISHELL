/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:39:24 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/08 01:16:52 by abadouab         ###   ########.fr       */
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

# define EXIT "\033[AMinishell >$ exit\n"
# define INIT "\033[A\n>   \n"
# define TRUE 1

# define GREEN "\033[1;32m"
# define YELOW "\033[1;33m"
# define REDCL "\033[1;31m"
# define RESET "\033[0m"

int	g_catch_signals;

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
	char				*value;
	char				**args;
	char				**expand;
	int					args_index;
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

// typedef struct s_command
// {
//     void	type;
// 	char	*command;
//     void	args;
//     void	redirection;
// }				command_t;

// Inject Spaces utils

int		count_op(char *s);
int		check_sep(char c);
void	copy_and_inject_spaces(t_inject_data *data, char *s, char *str);
int		check_par(char *s);

///////////////// PROTOTYPES TOKENIZATION /////////////////

int		cmp_operators(char c);
void	tokenize_operators(char *s, int *j, char **arr, int w);
void	get_tokens(char *s, int *j, char *quotes);
int		words_counter(const char *s);
char	**ft_split_op(t_allocate **leaks, char const *s);

int		check_token_op(char *token);
void	syntax_err(t_minishell *ms, char *error_msg, int exit_status);
void	set_redir(t_minishell *ms, int *i);
int		check_if_operator(char *token);
int		check_redirection(t_minishell *ms, int *i, int *redir_set);
void	check_args(t_tree *node, char **tokens, int len);
int		check_redir_at_end(t_minishell *ms, int *i, int *redir_set);
int		check_closed_quotes(t_minishell *ms, int i, int j);
int		check_valid_op(char *token);
void	set_op(t_tree *tree, char *token);

///////////////// HERE_DOC /////////////////

int		ft_open_here_doc(t_minishell *ms, char *delimiter);

t_tree	*parse_simple_command(t_minishell *ms, int *i);
t_tree	*parse_exp(t_minishell *ms, int *i, int min_pr);
t_tree	*parse_tree(t_minishell *ms);

///////////////// SIGNAL PROTOTYPES /////////////////

void	sig_handler(void);
void	sig_heredoc(void);

///////////////// ENVIRONMENT PROTOTYPES /////////////////

void	sort_export_vars(t_environ **export);
void	environment_init(t_minishell *ms, char **env);
void	environment_add(t_minishell *ms, t_environ **env, void *var, void *val);

///////////////// ERROR PROTOTYPES /////////////////

void	error_handler(t_minishell *ms);
int		check_syntax_err(t_minishell *ms);
int		check_token_if_redir(char *token);

///////////////// OTHER PROTOTYPES /////////////////

void	execution(t_minishell *ms, t_tree *tree, char **env);
char	**expanding(t_minishell *ms, char **expand);
char	*inject_spaces(t_minishell *ms, char *s);
int		check_ops_and_cmds(t_minishell *ms);

#endif
