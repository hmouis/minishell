/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:34:41 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/05/22 16:14:18 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_nodes(t_gnl *list)
{
	if (!list)
		return 0;
	t_gnl	*tmp;
	int		counter;

	tmp = list;
	counter = 0;
	while (tmp)
	{
		tmp = tmp->next;
		counter++;
	}
	return counter;
}

t_gnl	*cr_node(char *s)
{
	if (!s)
		return NULL;
	t_gnl	*node;

	node = ft_malloc(sizeof(t_gnl), 1);
	node->str = s;
	node->next = NULL;
	return node;
}

t_exec	*gnl_to_array(t_gnl *head)
{
	if (!head)
		return NULL;
	int	counter;
	int	i;
	t_exec	*arg;
	t_gnl	*tmp;

	tmp = head;
	counter = len_nodes(head);
	arg = ft_malloc(sizeof(t_exec), 1);
	arg->args = ft_malloc(sizeof(char *) * (counter + 1), 1);
	i = 0;
	while (tmp)
	{
		arg->args[i] = tmp->str;
		tmp = tmp->next;
		i++;
	}
	arg->args[i] = NULL;
	return arg;
}

