/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:12:31 by hmouis            #+#    #+#             */
/*   Updated: 2025/05/24 12:58:30 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
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

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

t_list **get_list()
{
	static t_list *list;
	return(&list);
}

void *ft_malloc(size_t size, int flag)
{
	t_list *node;
	void *ptr;

	node = NULL;
	ptr = NULL;
	if (flag == 0)
	{
		ft_lstclear(get_list(), free);
		return (NULL);
	}
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = ft_lstnew(ptr);
	if (!node)
		return (NULL);
	ft_lstadd_front(get_list(), node);
	return (ptr);
}
