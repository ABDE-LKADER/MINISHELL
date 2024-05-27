#ifndef MINISHELL_H
# define MINISHELL_H

# include "mylib.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_inject_data
{
	int		i;
	int		j;
	int		len;
	char	quotes;
}			t_inject_data;

// This structure holds the main state
//	and configurations for the M1N15H3LL program.

typedef struct s_minishell
{
	t_allocate		*leaks;
}					t_minishell;

// typedef enum	s_operator_type
// {
//     OP_AND,
//     OP_OR
// } 				operator_type_t;

// typedef struct s_logical_exp_node
// {
//     t_operator_type	operator;
//     void			*left;
//     void			*right;
// }				logical_exp_node_t;

int		cmp_operators(char c);
void	tokenize_operators(char *s, int *j, char **arr, int w);
void	get_tokens(char *s, int *j, char *quotes);
int		words_counter(const char *s, char c);
char	**ft_split_op(t_allocate **leaks, char const *s, char c);

#endif
