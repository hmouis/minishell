/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_of_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:50:08 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/04/22 14:28:42 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection(t_lst *lst)
{
	if (!lst->content)
		return (0);
	if (!ft_strcmp(lst->content, "<"))
	{
		lst->type = op_redirect_input;
		return (1);
	}
	else if (!ft_strcmp(lst->content, ">"))
	{
		lst->type = op_redirect_output;
		return (1);
	}
	else if (!ft_strcmp(lst->content, "<<"))
	{
		lst->type = op_herdoc;
		return (1);
	}
	else if (!ft_strcmp(lst->content, ">>"))
	{
		lst->type = op_append;
		return (1);
	}
	return (0);
}

void	is_pipe(t_lst **lst)
{
	if (!*lst)
		return ;
	if (!ft_strcmp((*lst)->content, "|"))
	{
		(*lst)->type = op_pipe;
		(*lst) = (*lst)->next;
		if ((*lst) && !is_operator((*lst)->content))
		{
			(*lst)->type = cmd;
			(*lst) = (*lst)->next;
		}
	}
}

void	type_redirection(t_lst **lst)
{
	if ((*lst)->type != op_herdoc)
	{
		(*lst) = (*lst)->next;
		if ((*lst) && !is_operator((*lst)->content))
		{
			(*lst)->type = file_name;
			(*lst) = (*lst)->next;
		}
	}
	else if ((*lst)->type == op_herdoc)
	{
		(*lst) = (*lst)->next;
		if ((*lst) && !is_operator((*lst)->content))
		{
			(*lst)->type = delimiter;
			(*lst) = (*lst)->next;
		}
	}
}

void	tokens_type(t_lst *lst)
{
	if (!is_operator(lst->content))
	{
		lst->type = cmd;
		lst = lst->next;
	}
	while (lst)
	{
		while (lst && !is_operator(lst->content))
		{
			lst->type = argument;
			lst = lst->next;
		}
		is_pipe(&lst);
		if (lst && is_redirection(lst))
			type_redirection(&lst);
	}
}
