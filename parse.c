#include "minishell.h"

int	check_token_op(char *token)
{
	char	*operators[4];
	int		i;

	operators[0] = "|";
	operators[1] = "||";
	operators[2] = "&&";
	operators[3] = NULL;

	if (!token)
		return(0);
	i = 0;
	while (operators[i])
	{
		if (ft_strncmp(token, operators[i], ft_strlen(token)))
			return (1);
		i++;
	}
	return (0);
}

logical_exp_node_t	parse_exp(char **tokens, int i)
{
	command_t	cmd;
	logical_exp_node_t exp;

	while (i > 0 && !tokens[i])
		i--;
	if (tokens[i - 1] && check_token_op(tokens[i]))
	{
		cmd.type = CMD;
		cmd.command = tokens[i - 1];
		exp.left = cmd;
	}
	else if (check_token_op(tokens[i]) && tokens[i + 1])
	{
		if (ft_strncmp(tokens[i + 1], "(", ft_strlen(tokens[i + 1])) == 0)
		{
			i += 2;
			while(!check_token_op(tokens[i]))
			{
				
			}
		}
	}

}

int parse(char **tokens)
{
	int	i;
	logical_exp_node_t exp;

	if (!tokens || !tokens[0])
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "(", ft_strlen(tokens[i])) == 0)
		{
			if (tokens[i - 1] && check_token_op(token[i - 1]))
				exp = parse_exp(tokens, (i - 1));
		}
		i++;
	}
}