/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:39:24 by abbaraka          #+#    #+#             */
/*   Updated: 2024/07/27 17:16:58 by abadouab         ###   ########.fr       */
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
int		check_op_syntax(char *token);
void	ft_treeadd_back(t_tree **lst, t_tree *new);
t_tree	*ft_treelast(t_tree *lst);

///////////////// HERE_DOC /////////////////

int		ft_open_here_doc(t_minishell *ms, char *delimiter, t_tree *node);
t_tree	*parse_simple_command(t_minishell *ms, int *i);
t_tree	*parse_exp(t_minishell *ms, int *i, int min_pr);
t_tree	*parse_tree(t_minishell *ms);

///////////////// SIGNAL PROTOTYPES /////////////////

void	sig_handler(void);
void	sig_heredoc(void);
void	sig_childer(void);
void	set_signals(int status);

///////////////// ENVIRONMENT PROTOTYPES /////////////////

void	environment_init(t_minishell *ms, char **env);
void	environment_add(t_minishell *ms, t_environ **env, void *var, void *val);
char	*get_env_val(t_minishell *ms, char *s);
void	modify_env_val(t_minishell *ms, char *env_var, char *val);
bool	search_env_var(t_environ *env, char *to_find);

///////////////// ERROR PROTOTYPES /////////////////

void	cleanup_handler(t_minishell *ms);
int		check_syntax_err(t_minishell *ms);
int		check_token_if_redir(char *token);
void	execution_errors(t_minishell *ms, t_tree *tree, char *path);
void	error_handler(t_minishell *ms, char *path);

///////////////// PIPES PROTOTYPES /////////////////

void	pipeline_handler(t_minishell *ms, t_tree *tree);

///////////////// REDIR PROTOTYPES /////////////////

t_fds	save_fds(void);
int		redirection(t_minishell *ms, t_tree *tree);
int		redir_to_dev_null(t_minishell *ms);
void	restore_fds(t_fds fds);
bool	check_ambiguous_redir(t_minishell *ms, char *name);
void	clean_fds(t_tree *tree);

///////////////// EXEC PROTOTYPES /////////////////

char	**change_linked_to_double(t_minishell *ms);
char	*fetch_path(t_minishell *ms, t_environ *env, char *cmd);
void	execution(t_minishell *ms, t_tree *tree);
void	built_in_execute(t_minishell *ms, t_tree *tree);

///////////////// EXPAND PROTOTYPES /////////////////

char	*splite_to_expand(t_minishell *ms, char *arg, int option);
char	*tilde_expander(t_minishell *ms, char *value);
char	*expand_val(t_minishell *ms, char *arg);
void	expand_add(t_minishell *ms, t_expand **expand, void *value);
char	*splite_mult_args(t_minishell *ms, char *arg, bool status, bool option);
void	expanding(t_minishell *ms, t_tree *tree, int index);
bool	expand_option(char *value, char *sp, int option);
int		here_doc_expander(t_minishell *ms, int fd);
char	**split_args(t_allocate **leaks, char *str, char *charset);
void	join_doubles(t_minishell *ms, t_tree *tree, char **join, int *index);
char	**wildcards_expander(t_minishell *ms, char *arg);
char	*remove_qoutes(t_minishell *ms, char *value);
void	convert_to_eot(t_expand *expand);
bool	split_expansion_checker(t_minishell *ms);
bool	only_var(t_minishell *ms, char *arg);

///////////////// BUILTINS PROTOTYPES /////////////////

int		check_if_builtins(char *cmd);
void	ft_export(t_minishell *ms, t_environ *env, char **args);
void	ft_unset(t_minishell *ms, char **args);
void	ft_env(t_minishell *ms, t_environ *env);
void	ft_echo(t_minishell *ms, char **args);
void	ft_pwd(t_minishell *ms);
void	ft_cd(t_minishell *ms, char **args);
void	ft_exit(t_minishell *ms, t_tree *tree, char **args);
bool	valid_identifier(char *str, int len);
bool	check_valid_identifier(char *str);

///////////////// OTHER PROTOTYPES /////////////////

void	save_termios_mode(t_minishell *ms, bool mode);

#endif
