/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:52:24 by hmouis            #+#    #+#             */
/*   Updated: 2025/05/02 18:30:43 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int pipe_line(t_lst *lst)
{
	while (lst)
	{
		while (lst && lst->type == word)
			lst = lst->next;
		if (!simple_command(&lst))
			return (0);
	}
	return (1);
}

int simple_command(t_lst **lst)
{
	if (*lst && (*lst)->type != op_pipe)
	{
		if (((*lst)->next && (*lst)->next->type != word) || !(*lst)->next)
			return (0);
		*lst = (*lst)->next;
	}
	else if (*lst && (*lst)->type == op_pipe)
	{
		if ((*lst)->next && (*lst)->next->type != word)
			return (0);
		*lst = (*lst)->next;
	}
	return (1);
}
