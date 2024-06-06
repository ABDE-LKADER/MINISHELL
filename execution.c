/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:54:33 by abadouab          #+#    #+#             */
/*   Updated: 2024/06/06 14:48:33 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_minishell *ms, t_tree *tree)
{
	if (!tree)
		return ;
	printf("\nBEFORE ------------------------------------------------------------\n");
	printf("%p\t\t\tVALUE ----------> %s\n", &ms->tree, tree->value);
	while (tree->expand && *tree->expand)
	{
		printf("----------> %s\n", *tree->expand);
		tree->expand++;
	}
	printf("\nEXPANDED ------------------------------------------------------------\n");
	while (tree->args && *tree->args)
	{
		printf("----------> %s\n", *tree->args);
		tree->args++;
	}
	execution(ms, tree->left);
	execution(ms, tree->right);
}
