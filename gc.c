/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:05:27 by hmouis            #+#    #+#             */
/*   Updated: 2025/05/07 10:26:30 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst(t_lst **lst)
{
	t_lst	*save;

	while (*lst)
	{
		save = (*lst)->next;
		free(*lst);
		*lst = save;
	}
}

void free_cmd(t_cmd **cmd)
{
	while (*cmd)
	{
		free_lst(&(*cmd)->arg);
		free_lst(&(*cmd)->redirect);
		*cmd = (*cmd)->next;
	}
}

void free_all(t_lst **lst, t_cmd **cmd)
{
	free_lst(lst);
	free_cmd(cmd);
}
