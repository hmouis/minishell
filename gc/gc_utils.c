/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:42:10 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 19:33:37 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list_env	*ft_lstnew_env(void *content)
{
	t_list_env	*node;

	node = malloc(sizeof(t_list_env));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_front_env(t_list_env **lst, t_list_env *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

t_list_env	**get_list_env(void)
{
	static t_list_env	*list_env;

	return (&list_env);
}

void	*ft_malloc_env(size_t size, int flag)
{
	t_list_env	*node;
	void		*ptr;

	node = NULL;
	ptr = NULL;
	if (flag == 0)
	{
		ft_lstclear_env(get_list_env(), free);
		return (NULL);
	}
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = ft_lstnew_env(ptr);
	if (!node)
		return (NULL);
	ft_lstadd_front_env(get_list_env(), node);
	return (ptr);
}
