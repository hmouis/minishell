/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 09:25:25 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/29 15:20:58 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*n_of_herdoc(t_lst *lst, int *status)
{
	int	number_of_herdoc;

	number_of_herdoc = 0;
	while (lst)
	{
		if (lst->type == op_herdoc)
			number_of_herdoc++;
		if (number_of_herdoc == 17)
		{
			*status = 1;
			return ("minishell: maximum here-document count exceeded");
			g_exit_status = 2;
		}
		lst = lst->next;
	}
	return (NULL);
}

char	*pipe_line(t_lst *lst, int *status)
{
	char	*err_msg;

	err_msg = NULL;
	if (lst->type == op_pipe)
		return (lst->content);
	err_msg = n_of_herdoc(lst, status);
	if (err_msg)
		return (err_msg);
	while (lst)
	{
		while (lst && lst->type == word)
		{
			err_msg = check_quote(lst->content);
			if (err_msg)
				return (err_msg);
			lst = lst->next;
		}
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
		if (!(*lst)->next)
			return ("end of file");
		if ((*lst)->next->type == op_pipe)
			return ((*lst)->next->content);
		*lst = (*lst)->next;
	}
	return (NULL);
}

void	allocate_herdoc(int *remainder, t_herdoc **herdoc)
{
	if (*remainder == 0)
		*remainder = 1;
	else
	{
		(*herdoc)->next = new_herdoc();
		*herdoc = (*herdoc)->next;
	}
}

t_cmd	*node(void)
{
	t_cmd	*cmd;

	cmd = ft_malloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->arg = NULL;
	cmd->args = NULL;
	cmd->redirect = NULL;
	cmd->next = NULL;
	return (cmd);
}
