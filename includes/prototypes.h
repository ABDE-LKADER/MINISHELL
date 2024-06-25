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

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "typedefs.h"

///////////////// INJECT-SPACES PROTOTYPES /////////////////

int		count_op(char *s);
int		check_sep(char c);
void	copy_and_inject_spaces(t_inject_data *data, char *s, char *str);
char	*inject_spaces(t_minishell *ms, char *s);
int		check_ops_and_cmds(t_minishell *ms);
int		check_par(char *s);

///////////////// PROTOTYPES TOKENIZATION /////////////////

int		cmp_operators(char c);
void	tokenize_operators(char *s, int *j, char **arr, int w);
void	get_tokens(char *s, int *j, char *quotes);
int		words_counter(const char *s);
char	**ft_split_op(t_allocate **leaks, char const *s);

///////////////// PARCE TOKENIZATION /////////////////

int		check_token_op(char *token);
void	syntax_err(t_minishell *ms, char *option,
			char *error_msg, int exit_status);
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
void	environment_init(t_minishell *ms, char **env, int ac, char **av);
void	environment_add(t_minishell *ms, t_environ **env, void *var, void *val);

///////////////// ERROR PROTOTYPES /////////////////

void	error_handler(t_minishell *ms);
int		check_syntax_err(t_minishell *ms);
int		check_token_if_redir(char *token);
void	execution_errors(t_minishell *ms, t_tree *tree, char *path);

///////////////// PIPES PROTOTYPES /////////////////

void	pipeline_handler(t_minishell *ms, t_tree *tree, char **env);

///////////////// REDIR PROTOTYPES /////////////////

void	redirection(t_tree *tree);
t_fds	save_fds(t_fds fds);
void	restore_fds(t_fds fds);

///////////////// EXEC PROTOTYPES /////////////////

void	execution(t_minishell *ms, t_tree *tree, char **env);
void	built_in_execute(t_minishell *ms, t_tree *tree);

///////////////// EXPAND PROTOTYPES /////////////////

char	*splite_to_expand(t_minishell *ms, char *arg);
void	expanding(t_minishell *ms, char **args);
char	*tilde_expander(t_environ *env);
char	*expand_val(t_minishell *ms, char *arg);
void	expand_add(t_minishell *ms, t_expand **expand, void *value);
char	*remove_duplicate_qoutes(t_minishell *ms, char *value);

///////////////// BUILTINS PROTOTYPES /////////////////

int		check_if_builtins(char *cmd);
void	ft_export(t_minishell *ms, t_environ *export, char **args);
void	ft_unset(t_minishell *ms, char **args);
void	ft_env(t_environ *env);
int		ft_echo(char **args);
int		ft_exit(char **args);
void	ft_pwd(void);
void	ft_cd(t_minishell *ms, char **args);

///////////////// OTHER PROTOTYPES /////////////////

#endif
