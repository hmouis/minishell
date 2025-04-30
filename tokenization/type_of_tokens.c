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



int	is_redirection(t_lst *list)
{
	if (!list->content)
		return 0;
	if (!ft_strcmp(list->content, "<"))
	{
		list->type = op_redirect_input;
		return 1;
	}
	else if (!ft_strcmp(list->content, ">"))
	{
		list->type = op_redirect_output;
		return 1;
	}
	else if (!ft_strcmp(list->content, "<<"))
	{
		list->type = op_herdoc;
		return 1;
	}
	else if (!ft_strcmp(list->content, ">>"))
	{
		list->type = op_append;
		return 1;
	}
	return 0;
}

int	is_pipe(t_lst *list)
{
	if (!list->content)
		return 0;
	if (!ft_strcmp(list->content, "|"))
		return 1;
	return 0;
}

/*void	tokens_type(t_lst *lst)*/
/*{*/
/*	if (!is_operator(lst->content))*/
/*		lst->type = cmd;*/
/*	while (lst)*/
/*	{*/
/*	}*/
/**/
/*}*/


