#ifndef MINISHELL_H
# define MINISHELL_H

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

size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

int		cmp_operators(char c);
void	tokenize_operators(char *s, int *j, char **arr, int w);
void	get_tokens(char *s, int *j, char *quotes);
int		words_counter(const char *s, char c);
char	**ft_split(char const *s, char c);
char	**ft_split_op(char const *s, char c);

#endif