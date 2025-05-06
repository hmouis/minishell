/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 09:25:25 by hmouis            #+#    #+#             */
/*   Updated: 2025/05/06 10:37:17 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*pipe_line(t_lst *lst)
{
	char	*err_msg;

	err_msg = NULL;
	if (lst->type == op_pipe)
		return (lst->content);
	while (lst)
	{
		while (lst && lst->type == word)
			lst = lst->next;
		err_msg = simple_command(&lst);
		if (err_msg)
			return (err_msg);
	}
	return (NULL);
}

char	*simple_command(t_lst **lst)
{
	if (*lst && (*lst)->type != op_pipe)
	{
		if (!(*lst)->next)
			return ("newline");
		if ((*lst)->next && (*lst)->next->type != word)
			return ((*lst)->next->content);
		*lst = (*lst)->next;
	}
	else if (*lst && (*lst)->type == op_pipe)
	{
		if ((*lst)->next && (*lst)->next->type != word)
			return ((*lst)->next->content);
		*lst = (*lst)->next;
	}
	return (NULL);
}

t_cmd	*node(t_lst *lst)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->arg = NULL;
	cmd->redirect = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*creat_cmd_struct(t_cmd **cmd, t_lst *lst)
{
	t_cmd	*head;

	*cmd = node(lst);
	head = *cmd;
	while (lst)
	{
		while (lst && lst->type == word)
		{
			add_to_lst(&(*cmd)->arg, lst->content);
			lst = lst->next;
		}
		if (lst && lst->type != op_pipe)
		{
			add_to_lst(&(*cmd)->redirect, lst->content);
			lst = lst->next;
			add_to_lst(&(*cmd)->redirect, lst->content);
			lst = lst->next;
		}
		if (lst && lst->type == op_pipe)
		{
			(*cmd)->next = node(lst);
			*cmd = (*cmd)->next;
			lst = lst->next;
		}
	}
	return (head);
}
