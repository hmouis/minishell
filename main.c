/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:06:13 by hmouis            #+#    #+#             */
/*   Updated: 2025/05/24 12:58:47 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*test_line = NULL;
	t_lst	*lst = NULL;
	t_final_struct	*fnl = NULL;
	t_cmd	*cmd = NULL;
	t_cmd	*head = NULL;
	char	*err_msg = NULL;
	int		i = 1;
	t_env	*list = NULL;
	t_gnl *gnl = NULL;
	t_new_exp *new_exp = NULL;
	t_cmd *tmp = NULL;
	t_herdoc *herdoc = NULL;
	t_final_struct *final_struct = NULL;

	while (1)
	{
		test_line = readline("minishell: ");
		add_history(test_line);
		if (!test_line)
		{
			ft_malloc(0,0);
			break ;
		}
		split_input(test_line, &lst);
		if (lst)
		{
			tokens_type(lst);
			err_msg = pipe_line(lst);
			if (err_msg)
			{
				error_msg(err_msg);
				printf("\n");
				lst = NULL;
				continue;
			}
			else
				cmd = creat_cmd_struct(&cmd, lst);
		}
		add_env_to_list(&list, env);
		builtin_export(&list, "x=hello ");
		int a = 0;
		t_final_struct *tmp = NULL;
		t_cmd *c_tmp = NULL;
		c_tmp = cmd;

		while (cmd)
		{
			if (a == 1)
				herdoc = fill_herdoc(cmd->redirect, list, &herdoc);
			if (a == 0)
			{
				herdoc = fill_herdoc(cmd->redirect, list, &herdoc);
				fnl	= creat_new_exp(list, &new_exp, cmd, &fnl);
				tmp = fnl;
				a = 1;
			}
			fnl->herdoc = herdoc;
			cmd = cmd->next;
			fnl = fnl->next;
		}
		while (tmp)
		{
			while (tmp->args)
			{
				printf("arg = %s <--> type %d \n",tmp->args->str, tmp->args->type);
				tmp->args = tmp->args->next;
			}
			while (tmp->redirect)
			{
				printf("red = %s <--> type %d \n",tmp->redirect->str, tmp->redirect->type);
				tmp->redirect = tmp->redirect->next;
			}
			while (tmp->herdoc && tmp->herdoc->list)
			{
				printf("%s <--> type %d",tmp->herdoc->list->str, tmp->herdoc->list->type);
				tmp->herdoc->list	= tmp->herdoc->list->next;
			}
			tmp = tmp->next;
			if (tmp)
				printf ("------------------------\n---------------------\n");
		}
		tmp = NULL;
		cmd = NULL;
		lst = NULL;
	}

}





