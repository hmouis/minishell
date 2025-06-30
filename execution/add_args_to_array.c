/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_args_to_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:34:41 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 22:29:24 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "../includes/gc.h"

int	len_nodes(t_gnl *list)
{
	t_gnl	*tmp;
	int		counter;

	if (!list)
		return (0);
	tmp = list;
	counter = 0;
	while (tmp)
	{
		if (!tmp->str)
		{
			tmp = tmp->next;
			continue ;
		}
		tmp = tmp->next;
		counter++;
	}
	return (counter);
}

t_gnl	*cr_node(char *s)
{
	t_gnl	*node;

	if (!s)
		return (NULL);
	node = ft_malloc(sizeof(t_gnl), 1);
	node->str = s;
	node->next = NULL;
	return (node);
}

t_exec	*gnl_to_array(t_gnl *head)
{
	int		counter;
	int		i;
	t_exec	*arg;
	t_gnl	*tmp;

	if (!head)
		return (NULL);
	tmp = head;
	counter = len_nodes(head);
	arg = ft_malloc(sizeof(t_exec), 1);
	arg->args = ft_malloc(sizeof(char *) * (counter + 1), 1);
	i = 0;
	while (tmp)
	{
		if (!tmp->str)
		{
			tmp = tmp->next;
			continue ;
		}
		arg->args[i] = tmp->str;
		tmp = tmp->next;
		i++;
	}
	arg->args[i] = NULL;
	return (arg);
}
