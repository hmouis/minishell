/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:06:13 by hmouis            #+#    #+#             */
/*   Updated: 2025/05/21 18:49:20 by hmouis           ###   ########.fr       */
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
	t_exp *exp = NULL;
	t_env	*list = NULL;
	t_gnl *gnl = NULL;
	t_new_exp *new_exp = NULL;
	t_final_struct *final_struct = NULL;

	add_env_to_list(&list, env);
	while (1)
	{
		test_line = readline("minishell: ");
		add_history(test_line);
		if (!test_line)
			break ;
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
		if (cmd)
			fnl = creat_new_exp(list, &new_exp, cmd, &fnl);
		if (fnl && fnl->args)
		{
			t_exec *exec = gnl_to_array(fnl->args);
			int redirect = -1;
			char *file = NULL;
			if (fnl->redirect && fnl->redirect->next)
				file = fnl->redirect->next->str;
			if (fnl->redirect)
			{
				redirect = type_of_redirect(fnl->redirect->str);
			}
			if (is_builtins(fnl->args->str) != -1)
				exec_builtins(&list, exec->args, file, redirect);
			else
				exec_cmd(exec->args, fnl->args->str, file, redirect);
			fnl->args = fnl->args->next;
		}
		free(test_line);
		cmd = NULL;
		lst = NULL;
	}
}

