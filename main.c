/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:06:13 by hmouis            #+#    #+#             */
/*   Updated: 2025/05/22 18:13:45 by hmouis           ###   ########.fr       */
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
		builtin_export(&list, "x=    ls   -l ");
		if (cmd)
		   fnl	= creat_new_exp(list, &new_exp, cmd, &fnl);
		while (fnl)
		{
			while (fnl->args)
			{
				printf("args = %s\n",fnl->args->str);
				fnl->args = fnl->args->next;
			}
			while (fnl->redirect)
			{
				printf("redirection = %s\n",fnl->redirect->str);
				fnl->redirect = fnl->redirect->next;
			}
			fnl = fnl->next;
			if (fnl)
				printf ("------------------------\n---------------------\n");
		}
		/*while (new_exp)*/
		/*{*/
		/*	while (new_exp->string)*/
		/*	{*/
		/*		printf("new_str = {%s}-->{type = %d}\n",new_exp->string->content, new_exp->string->type);*/
		/*		new_exp->string = new_exp->string->next;*/
		/*	}*/
		/*	new_exp = new_exp->next;*/
		/*	printf("--------------------\n");*/
		/*}*/
		cmd = NULL;
		lst = NULL;
	}

}





