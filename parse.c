#include "minishell.h"

int check_closed_par(char *token)
{
    int i;
    int level;

    i = 0;
    level = 0;
    while (token[i])
    {
        if (token[i] == '(')
            level++;
        if (token[i] == ')')
            level--;
        i++;
    }
    if (level == 0)
        return (1);
    return (0);
}

char    *remove_par(char *token)
{
    int     i;
    int     j;
    int     len;
    char    *new;

    len = ft_strlen(token) - 2;
    new = malloc((len + 1) * sizeof(char));
    i = 1;
    j = 0;
    while (token[i])
    {
        if (i == len + 1)
            break ;
        new[j] = token[i];
        i++;
        j++;
    }
    new[j] = '\0';
    free(token);
    return (new);
}

logical_exp_node_t  *parse_term(char **tokens, int *i)
{
    logical_exp_node_t  *exp;
    char                *new;
    if (tokens[*i] != NULL, && tokens[*i][0] == '(' && check_closed_par(token))
    {
        tokens[*i] = remove_par(tokens[*i]);
        exp = parse_exp(tokens, i);
        
    }
}

logical_exp_node_t    parse_exp(char **tokens, int *i)
{
    t_logical_exp_node  *left; 

    left = parse_term(tokens, i);
    // while (tokens[i])
    // {
    //     left = 
    // }
}

int parse(char **tokens)
{
    logical_exp_node_t  *root;
    int                 i;

    i = 0;
    root = parse_exp(tokens, &i);
    
}
