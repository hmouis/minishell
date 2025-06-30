/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils__2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:44:24 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/29 16:44:48 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pars_fnl_utils(t_final_struct **tmp, t_v *va, t_gnl **head, t_gnl **arg)
{
	while ((*tmp)->args)
	{
		if ((*tmp)->args && (*tmp)->args->str[0] == '\0'
			&& (*tmp)->args->type == 6)
		{
			va->reminder = 1;
			(*tmp)->args = (*tmp)->args->next;
			continue ;
		}
		if (!va->flag)
		{
			va->flag = 1;
			*arg = final_node((*tmp)->args->str, (*tmp)->args->type);
			*head = *arg;
		}
		else
		{
			(*arg)->next = final_node((*tmp)->args->str, (*tmp)->args->type);
			*arg = (*arg)->next;
		}
		(*tmp)->args = (*tmp)->args->next;
	}
}

t_final_struct	*pars_fnl(t_final_struct *fnl)
{
	t_final_struct	*tmp;
	t_gnl			*arg;
	t_gnl			*head;
	t_v				va;

	va.reminder = 0;
	va.flag = 0;
	tmp = fnl;
	head = NULL;
	arg = NULL;
	while (tmp)
	{
		pars_fnl_utils(&tmp, &va, &head, &arg);
		if (va.reminder == 1 && !va.flag && !tmp->next)
		{
			g_exit_status = 0;
			return (NULL);
		}
		va.flag = 0;
		va.reminder = 0;
		tmp->args = head;
		tmp = tmp->next;
	}
	return (fnl);
}

int	check_herdoc(t_herdoc **herdoc, t_lst *red, t_env *list)
{
	*herdoc = fill_herdoc(red, list, herdoc);
	if (!*herdoc && g_exit_status == 130)
		return (1);
	return (0);
}

t_final_struct	*fill_fnl(t_cmd *cmd, t_final_struct *fnl, t_env *list)
{
	t_new_exp		*exp;
	t_herdoc		*herdoc;
	int				flag;
	t_final_struct	*tmp;

	exp = NULL;
	tmp = NULL;
	flag = 0;
	herdoc = NULL;
	while (cmd)
	{
		if (flag == 1 && check_herdoc(&herdoc, cmd->redirect, list))
			return (NULL);
		if (flag == 0)
		{
			if (check_herdoc(&herdoc, cmd->redirect, list))
				return (NULL);
			fnl = creat_new_exp(list, &exp, cmd, &fnl);
			tmp = fnl;
			flag = 1;
		}
		move_struct(&fnl, &cmd, herdoc);
	}
	// tmp = pars_fnl(tmp);
	return (tmp);
}

void	handle_sig(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	if (!change_value(2))
		write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 130;
}
