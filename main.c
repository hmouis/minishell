/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:04:20 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/26 15:07:26by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	empty__line(void)
{
	ft_malloc(0, 0);
	printf("exit\n");
	exit(0);
}

int	tokenize_input(char *line, t_cmd **cmd)
{
	int		status;
	t_lst	*lst;
	char	*err_msg;

	if (!line)
		empty__line();
	lst = NULL;
	err_msg = NULL;
	status = 0;
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

t_final_struct	*pars_fnl(t_final_struct *fnl)
{
	t_final_struct	*tmp;
	t_gnl			*arg;
	t_gnl			*head;
	int				reminder;
	int				flag;

	reminder = 0;
	flag = 0;
	tmp = fnl;
	head = NULL;
	arg = NULL;
	while (tmp)
	{
		while (tmp->args)
		{
			if (tmp->args && tmp->args->str[0] == '\0' && tmp->args->type == 6)
			{
				reminder = 1;
				tmp->args = tmp->args->next;
				continue ;
			}
			if (!flag)
			{
				flag = 1;
				arg = final_node(tmp->args->str, tmp->args->type);
				head = arg;
			}
			else
			{
				arg->next = final_node(tmp->args->str, tmp->args->type);
				arg = arg->next;
			}
			tmp->args = tmp->args->next;
		}
		if (reminder == 1 && !flag && !tmp->next)
		{
			g_exit_status = 0;
			return (NULL);
		}
		flag = 0;
		reminder = 0;
		tmp->args = head;
		tmp = tmp->next;
	}
	return (fnl);
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
		if (flag == 1)
		{
			herdoc = fill_herdoc(cmd->redirect, list, &herdoc);
			if (!herdoc && g_exit_status == 130)
				return (NULL);
		}
		if (flag == 0)
		{
			herdoc = fill_herdoc(cmd->redirect, list, &herdoc);
			if (!herdoc && g_exit_status == 130)
				return (NULL);
			fnl = creat_new_exp(list, &exp, cmd, &fnl);
			tmp = fnl;
			flag = 1;
		}
		move_struct(&fnl, &cmd, herdoc);
	}
	tmp = pars_fnl(tmp);
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

int				g_exit_status;

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_final_struct	*fnl;
	t_cmd			*cmd;
	t_env			*list;

	line = NULL;
	fnl = NULL;
	cmd = NULL;
	list = NULL;
	add_env_to_list(&list, env);
	(void)ac;
	(void)av;
	while (1)
	{
		signal(SIGINT, handle_sig);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell~ ");
		change_value(0);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		add_history(line);
		if (!tokenize_input(line, &cmd))
			continue ;
		fnl = fill_fnl(cmd, fnl, list);
		if (cmd && fnl && fnl->herdoc)
			pars_herdoc(fnl, cmd->redirect);
		if (fnl)
			execute(fnl, list, env);
		cmd = NULL;
		fnl = NULL;
		free(line);
	}
}
