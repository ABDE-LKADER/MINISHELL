/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:17:56 by abadouab          #+#    #+#             */
/*   Updated: 2023/12/08 11:10:02 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*list;

	list = NULL;
	while (lst && f && del)
	{
		node = ft_lstnew(lst->content);
		if (!node)
			return (ft_lstclear(&list, del), NULL);
		node->content = f(lst->content);
		ft_lstadd_back(&list, node);
		lst = lst->next;
	}
	return (list);
}
