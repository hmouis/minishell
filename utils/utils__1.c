/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils__1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:43:27 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/29 16:44:16 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	assigne_tokeniz_input(int *status, char *line)
{
	if (!line)
		empty__line();
	*status = 0;
}

int	tokenize_input(char *line, t_cmd **cmd)
{
	int		status;
	t_lst	*lst;
	char	*err_msg;

	assigne_tokeniz_input(&status, line);
	lst = NULL;
	err_msg = NULL;
	split_input(line, &lst);
	if (!lst)
		return (0);
	if (lst)
	{
		tokens_type(lst);
		err_msg = pipe_line(lst, &status);
		if (err_msg)
		{
			error_msg(err_msg, status);
			status = 0;
			lst = NULL;
			return (0);
		}
		else
			*cmd = creat_cmd_struct(cmd, lst);
	}
	return (1);
}

void	process_herdoc_list(t_final_struct *fnl, t_lst **lst)
{
	t_gnl	*s1;
	t_gnl	*s2;

	while (*lst)
	{
		if ((*lst)->type != op_herdoc)
		{
			(*lst) = (*lst)->next->next;
			fnl->redirect = fnl->redirect->next;
			while (fnl->redirect && (fnl->redirect->type == -1
					|| fnl->redirect->type == var))
				fnl->redirect = fnl->redirect->next;
			continue ;
		}
		(*lst) = (*lst)->next;
		s1 = fnl->redirect;
		fnl->redirect = fnl->redirect->next;
		while (fnl->redirect && (fnl->redirect->type == -1
				|| fnl->redirect->type == var))
			fnl->redirect = fnl->redirect->next;
		s2 = fnl->redirect;
		s1->next = final_node((*lst)->content, -1);
		s1->next->next = s2;
		(*lst) = (*lst)->next;
	}
}

void	pars_herdoc(t_final_struct *fnl, t_lst *lst)
{
	t_gnl	*save;

	while (fnl)
	{
		save = fnl->redirect;
		process_herdoc_list(fnl, &lst);
		fnl->redirect = save;
		fnl = fnl->next;
	}
}

void	move_struct(t_final_struct **fnl, t_cmd **cmd, t_herdoc *herdoc)
{
	(*fnl)->herdoc = herdoc;
	*fnl = (*fnl)->next;
	*cmd = (*cmd)->next;
}
