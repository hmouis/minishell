/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:39:42 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 22:30:25 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "../includes/expansions.h"

void	update_env(t_env **env, char *oldpwd, char *pwd)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
			tmp->data = oldpwd;
		if (ft_strcmp(tmp->key, "PWD") == 0)
			tmp->data = pwd;
		tmp = tmp->next;
	}
}

void	split_handle_herdoc(int fd2, t_herdoc *herdoc)
{
	ssize_t	count;

	count = 0;
	while (herdoc)
	{
		if (!herdoc->next)
			break ;
		herdoc = herdoc->next;
	}
	while (herdoc->list)
	{
		count = write(fd2, herdoc->list->str, str_len(herdoc->list->str));
		if (count < 0)
		{
			perror("write");
			close(fd2);
			exit(1);
		}
		herdoc->list = herdoc->list->next;
	}
}

void	assigned_var(t_final_struct *tmp, char **file, t_apply_red *vars)
{
	vars->redirect = tmp->redirect->type;
	*file = tmp->redirect->next->str;
}
