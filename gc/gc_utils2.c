/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:31:55 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 22:49:28 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"

void	ft_lstdelone_env(t_list_env *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

void	ft_lstclear_env(t_list_env **lst, void (*del)(void *))
{
	t_list_env	*p;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		p = *lst;
		(*lst) = (*lst)->next;
		ft_lstdelone_env(p, del);
	}
	*lst = NULL;
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		p = *lst;
		(*lst) = (*lst)->next;
		ft_lstdelone(p, del);
	}
	*lst = NULL;
}
